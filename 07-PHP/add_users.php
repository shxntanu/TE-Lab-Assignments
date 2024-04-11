<?php
include 'db.php';

$name = $_POST['name'];
$email = $_POST['email'];
$age = $_POST['age'];

$sql = "INSERT INTO users (name, email, age) VALUES ('$name', '$email', '$age')";

if ($conn->query($sql) === TRUE) {
    header("Location: index.php");
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
