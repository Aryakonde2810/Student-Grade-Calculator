const form = document.getElementById("gradeForm");
const resultDiv = document.getElementById("result");

form.addEventListener("submit", async function (event) {
    event.preventDefault();

    const studentName = document.getElementById("studentName").value.trim();
    const rollNumber = document.getElementById("rollNumber").value.trim();

    const marks = [
        Number(document.getElementById("subject1").value),
        Number(document.getElementById("subject2").value),
        Number(document.getElementById("subject3").value),
        Number(document.getElementById("subject4").value),
        Number(document.getElementById("subject5").value)
    ];

    // Validate marks
    if (marks.some(mark =>
        !Number.isInteger(mark) || mark < 0 || mark > 100
    )) {
        resultDiv.textContent = "Please enter valid marks between 0 and 100.";
        return;
    }

    resultDiv.textContent = "Calculating your grade...";

    try {
        const response = await fetch(
            "http://127.0.0.1:8000/api/calculate",
            {
                method: "POST",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify(marks)
            }
        );

        const data = await response.json();

        if (!response.ok) {
            throw new Error(data.error || "Calculation failed.");
        }

        const status = data.passed ? "PASS" : "FAIL";

        resultDiv.innerHTML = `
            <h3>Student Result</h3>
            <p><strong>Name:</strong> ${escapeHTML(studentName)}</p>
            <p><strong>Roll Number:</strong> ${escapeHTML(rollNumber)}</p>
            <p><strong>Total Marks:</strong> ${data.total}/500</p>
            <p><strong>Percentage:</strong> ${data.percentage}%</p>
            <p><strong>Grade:</strong> ${data.grade}</p>
            <p><strong>Result:</strong> ${status}</p>
        `;

    } catch (error) {
        resultDiv.textContent =
            "Unable to connect to the C server. Make sure it is running. " +
            error.message;
    }
});

// Safely display student-provided text
function escapeHTML(value) {
    return value.replace(/[&<>"']/g, function (character) {
        const entities = {
            "&": "&amp;",
            "<": "&lt;",
            ">": "&gt;",
            '"': "&quot;",
            "'": "&#39;"
        };

        return entities[character];
    });
}

// Clear previous results when Reset is clicked
form.addEventListener("reset", function () {
    resultDiv.innerHTML = "";
});