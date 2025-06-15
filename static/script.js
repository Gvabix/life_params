const MAX_POINTS = 20;
const buffers = { spo2: [], hr: [], temp: [], gsr: []};

const makeConfig = (label, data) => ({
    type: 'line',
    data: {
        labels: Array(data.length).fill(''),
        datasets: [{
            label, data, borderWidth: 2, fill: false, tension: 0.3
        }]
    },
    options: {
        animation: false,
        scales: { y: { beginAtZero: false } },
        plugins: { legend: { display: false } }
    }
});

document.addEventListener('DOMContentLoaded', async () => {
    const charts = {
        spo2: new Chart(document.getElementById('spo2Chart'), makeConfig('SpO₂ [%]', buffers.spo2)),
        hr:   new Chart(document.getElementById('hrChart'),   makeConfig('HR [bpm]', buffers.hr)),
        temp: new Chart(document.getElementById('tempChart'), makeConfig('Temp [°C]', buffers.temp)),
        gsr:  new Chart(document.getElementById('gsrChart'),  makeConfig('GSR', buffers.gsr))
    };

    await fetchAndRender(charts);
    setInterval(() => fetchAndRender(charts), 5000);
});

// Funkcja do przycinania tablicy i dodawania nowej wartości
function pushAndTrim(buffer, value) {
    buffer.push(value);
    if (buffer.length > MAX_POINTS) {
        buffer.shift();
    }
}

async function fetchData() {
    const age = document.getElementById('age').value;
    const gender = document.getElementById('gender').value;
    await fetch(`/update?age=${age}&gender=${gender}`);
}

async function predict() {
    await fetch('/predict');
}

async function fetchAndRender(charts) {
    const age = document.getElementById('age').value;
    const gender = document.getElementById('gender').value;
    const res = await fetch(`/update?age=${age}&gender=${gender}`);
    const data = await res.json();

    // Aktualizacja tekstu
    ['spo2','hr','temp','gsr','samples'].forEach(k => {
        document.getElementById(k).innerText = data[k];
    });
    document.getElementById('status').innerText = data.status;
    document.getElementById('probability').innerText = data.probability.toFixed(2);

    // Aktualizacja alertów (zakładam, że masz <div id="alerts-container"> w HTML)
    const alertsContainer = document.getElementById('alerts-container');
    if (data.alerts && data.alerts.length > 0) {
        alertsContainer.innerHTML = data.alerts.map(alert => `<div class="alert-message">${alert}</div>`).join('');
    } else {
        alertsContainer.innerHTML = '<div class="alert-message">Wszystkie dane w normie</div>';
    }

    // Dane do wykresów
    pushAndTrim(buffers.spo2, data.spo2);
    pushAndTrim(buffers.hr, data.hr);
    pushAndTrim(buffers.temp, data.temp);
    pushAndTrim(buffers.gsr, data.gsr);

    Object.entries(charts).forEach(([key, chart]) => {
        chart.data.labels = Array(buffers[key].length).fill('');
        chart.data.datasets[0].data = buffers[key];
        chart.update();
    });

    // 🔁 Automatyczna predykcja po 20 i co każde kolejne 5 próbek
    if (data.samples >= 20 && data.samples % 5 === 0) {
        await predict();
    }
}


function pushAndTrim(arr, val) {
    arr.push(val);
    if (arr.length > MAX_POINTS) arr.shift();
}
