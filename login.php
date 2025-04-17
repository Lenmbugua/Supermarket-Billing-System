<?php
$servername = "localhost";
$username = "root"; // Update this
$password = ""; // Update this
$dbname = "supermarket_db";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("❌ Connection failed: " . $conn->connect_error);
}

// Handle login
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $user = $_POST["username"];
    $pass = $_POST["password"];

    $sql = "SELECT * FROM users WHERE username = '$user'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        if (password_verify($pass, $row["password"])) {
            echo "✅ Login successful!";
        } else {
            echo "❌ Invalid credentials!";
        }
    } else {
        echo "❌ User not found!";
    }
}

$conn->close();
?>