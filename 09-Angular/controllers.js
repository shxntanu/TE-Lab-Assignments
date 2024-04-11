app.controller('RegistrationController', function($scope, $location) {
  $scope.user = {};
  $scope.errorMessage = "";

  $scope.register = function() {
    console.log("Registering user:", $scope.user);
    $location.path('/login'); // Redirect to login after successful registration (simulated)
  };
});

app.controller('LoginController', function($scope, $location) {
  $scope.user = {};
  $scope.errorMessage = "";

  $scope.login = function() {

    if ($scope.user.username === "admin" && $scope.user.password === "password") {
      console.log("Login successful!");
      $location.path('/dashboard');
    } else {
      $scope.errorMessage = "Invalid username or password";
    }
  };
});
