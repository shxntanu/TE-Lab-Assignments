let currentNumber = "";
let previousNumber = "";
let operator = "";

function appendNumber(number) {
    if (currentNumber === "0" && number !== ".") {
        currentNumber = number;
    } else {
        currentNumber += number;
    }
    document.getElementById("result").value = currentNumber;
}

function clearResult() {
    currentNumber = "";
    previousNumber = "";
    operator = "";
    document.getElementById("result").value = "";
}

function appendOperator(op) {
    if (currentNumber !== "") {
        previousNumber = currentNumber;
        currentNumber = "";
        operator = op;
    } else {
        alert("Please enter a number before operator.");
    }
}

function calculate() {
    if (currentNumber !== "" && operator !== "") {
        let result;
        switch (operator) {
            case "+":
                result = parseFloat(previousNumber) + parseFloat(currentNumber);
                break;
            case "-":
                result = parseFloat(previousNumber) - parseFloat(currentNumber);
                break;
            case "*":
                result = parseFloat(previousNumber) * parseFloat(currentNumber);
                break;
            case "/":
                if (currentNumber === "0") {
                    alert("Division by zero is not allowed.");
                    return;
                }
                result = parseFloat(previousNumber) / parseFloat(currentNumber);
                break;
            default:
                alert("Invalid operator.");
                return;
        }
        currentNumber = result.toString();
        previousNumber = "";
        operator = "";
        document.getElementById("result").value = currentNumber;
    } else {
        alert("Please enter both numbers and an operator to calculate.");
    }
}

function squareRoot() {
    if (currentNumber !== "") {
        let result = Math.sqrt(parseFloat(currentNumber));
        currentNumber = result.toString();
        document.getElementById("result").value = currentNumber;
    } else {
        alert("Please enter a number to calculate square root.");
    }
}

// Add buttons for square root and handle decimal point entry
const calculator = document.getElementById("calculator");

const squareRootButton = document.createElement("button");
squareRootButton.textContent = "√";
squareRootButton.addEventListener("click", squareRoot);
calculator.appendChild(squareRootButton);

const decimalButton = document.createElement("button");
decimalButton.textContent = ".";
decimalButton.addEventListener("click", () => handleDecimal("."));
calculator.appendChild(decimalButton);

function handleDecimal(decimal) {
    if (!currentNumber.includes(".")) {
        currentNumber += decimal;
    } else {
        alert("Decimal point already entered.");
    }
    document.getElementById("result").value = currentNumber;
}

// Optional: Add buttons and validation for other operations
// You can expand the functionality by adding buttons for other
// mathematical operations and implementing validation accordingly.
