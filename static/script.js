async function fetchData() {
    const age = document.getElementById('age').value;
    const gender = document.getElementById('gender').value;
    // Store in the backend state
    await fetch(`/update?age=${age}&gender=${gender}`);
    updateDisplay();
}

async function predict() {
    await fetch('/predict');
    updateDisplay();
}

async function updateDisplay() {
    const response = await fetch('/update');
    const data = await response.json();
    document.getElementById('spo2').innerText = data.spo2;
    document.getElementById('hr').innerText = data.hr;
    document.getElementById('temp').innerText = data.temp;
    document.getElementById('gsr').innerText = data.gsr;
    document.getElementById('ecg').innerText = data.ecg;
    document.getElementById('samples').innerText = data.samples;
    document.getElementById('status').innerText = data.status;
    document.getElementById('probability').innerText = data.probability.toFixed(2);
}

setInterval(fetchData, 5000); // auto-refresh every 5 seconds
