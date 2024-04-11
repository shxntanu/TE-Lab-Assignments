var app = angular.module('registrationApp', ['ngRoute']);

app.config(function($routeProvider) {
  $routeProvider
    .when('/register', {
      templateUrl: 'registration.html',
      controller: 'RegistrationController'
    })
    .when('/login', {
      templateUrl: 'login.html',
      controller: 'LoginController'
    })
    .otherwise({ redirectTo: '/register' });
});
