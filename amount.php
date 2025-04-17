<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "supermarket_db";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("❌ Connection failed: " . $conn->connect_error);
}

// Handle purchase
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $item_id = $_POST["item_id"];
    $quantity = $_POST["quantity"];

    // Get item price
    $sql_item = "SELECT item_price FROM items WHERE item_id = $item_id";
    $result_item = $conn->query($sql_item);
    $row_item = $result_item->fetch_assoc();
    $item_price = $row_item["item_price"];
    $total_price = $item_price * $quantity;

    // Save amount record
    $sql_amount = "INSERT INTO amount (item_id, quantity, total_price) VALUES ($item_id, $quantity, $total_price)";
    if ($conn->query($sql_amount) === TRUE) {
        echo "✅ Purchase recorded!";
    } else {
        echo "❌ Error: " . $conn->error;
    }
}

$conn->close();
?>