<?php
// Database connection
$conn = new mysqli("localhost", "root", "", "supermarket_db");

if ($conn->connect_error) {
    die("❌ Connection failed: " . $conn->connect_error);
}

// Handle item addition
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $item_name = $_POST["item_name"];
    $item_price = $_POST["item_price"];

    // Insert new item into MySQL
    $sql = "INSERT INTO items (item_name, item_price) VALUES ('$item_name', '$item_price')";
    if ($conn->query($sql) === TRUE) {
        echo "✅ Item added successfully!";
    } else {
        echo "❌ Error: " . $conn->error; // Debugging output
    }
}

$conn->close();
?>