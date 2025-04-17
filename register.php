<?php
$servername = "localhost";
$username = "root"; // Update if needed
$password = ""; // Update if needed
$dbname = "supermarket_db";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("❌ Connection failed: " . $conn->connect_error);
}

// Handle user registration
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $user = $_POST["username"];
    $pass = password_hash($_POST["password"], PASSWORD_BCRYPT); // Secure password hashing

    $sql = "INSERT INTO users (username, password) VALUES ('$user', '$pass')";
    if ($conn->query($sql) === TRUE) {
        echo "✅ Registration successful!";
    } else {
        echo "❌ Error: " . $conn->error;
    }
}

$conn->close();
?>