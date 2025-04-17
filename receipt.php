<?php
// Database connection
$conn = new mysqli("localhost", "root", "", "supermarket_db");

if ($conn->connect_error) {
    die("❌ Connection failed: " . $conn->connect_error);
}

// Generate receipt & store purchase details
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $user_id = $_POST["user_id"];
    $item_id = $_POST["item_id"];
    $quantity = $_POST["quantity"];

    // Fetch item price
    $sql_item = "SELECT item_price FROM items WHERE item_id = $item_id";
    $result_item = $conn->query($sql_item);
    $row_item = $result_item->fetch_assoc();
    $item_price = $row_item["item_price"];
    $total_price = $item_price * $quantity;

    // Insert purchase details into `amount` table
    $sql_amount = "INSERT INTO amount (item_id, quantity, total_price) VALUES ($item_id, $quantity, $total_price)";
    if ($conn->query($sql_amount) === TRUE) {
        $amount_id = $conn->insert_id; // Get last inserted ID

        // Insert into receipts table
        $sql_receipt = "INSERT INTO receipts (user_id, amount_id) VALUES ($user_id, $amount_id)";
        if ($conn->query($sql_receipt) === TRUE) {
            echo "✅ Receipt saved successfully!";
        } else {
            echo "❌ Error saving receipt: " . $conn->error;
        }
    } else {
        echo "❌ Error recording purchase: " . $conn->error;
    }
}

$conn->close();
?>