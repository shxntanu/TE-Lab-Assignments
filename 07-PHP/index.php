<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>User Management</title>
</head>
<body>
    <h2>Add User</h2>
    <form action="add_user.php" method="post">
        Name: <input type="text" name="name"><br>
        Email: <input type="email" name="email"><br>
        Age: <input type="number" name="age"><br>
        <input type="submit" value="Add User">
    </form>

    <h2>Users List</h2>
    <?php include 'list_users.php'; ?>
</body>
</html>
