<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>SalEats - Login</title>
<link href='https://fonts.googleapis.com/css?family=Lobster' rel='stylesheet'>
<link rel="stylesheet" href="login.css">
<script src="https://kit.fontawesome.com/bbf7324bbf.js" crossorigin="anonymous"></script>
<meta name="google-signin-client_id" content="187007187865-kvpt9eraejgfmv22m41jj1c1794tgj81.apps.googleusercontent.com">
<script src="https://apis.google.com/js/api:client.js"></script>
<script>
function onSignIn(googleUser) {
	console.log("called");
	  var profile = googleUser.getBasicProfile();
	  console.log('ID: ' + profile.getId()); // Do not send to your backend! Use an ID token instead.
	  console.log('Name: ' + profile.getName());
	  console.log('Image URL: ' + profile.getImageUrl());
	  console.log('Email: ' + profile.getEmail()); // This is null if the 'email' scope is not present.
	  document.location.href = "google-login?username=" + profile.getName() + "&email=" + profile.getEmail();
	}
  var googleUser = {};
  var startApp = function() {
    gapi.load('auth2', function(){
      auth2 = gapi.auth2.init({
        client_id: '187007187865-kvpt9eraejgfmv22m41jj1c1794tgj81.apps.googleusercontent.com',
        cookiepolicy: 'single_host_origin',
      });
      attachSignin(document.getElementById('customBtn'));
    });
  };

  function attachSignin(element) {
    console.log(element.id);
    auth2.attachClickHandler(element, {},
        function(googleUser) {
			onSignIn(googleUser);
        }, function(error) {
        });
  }
  </script>
<style type="text/css">
#customBtn {
	height: 5.5vh; width: 100%; border-radius: 5px; border: 1px solid grey;  margin-bottom: 0.8vh;
	color: white; font-size: 2vh; font-family: 'Arial'; background-color: #4285F4; text-align: center; line-height: 5.5vh;
	
}
</style>
</head>
<body>
<div class="topnav">
	<ul>
		<li><a href="index.jsp" id="logo">SalEats!</a></li>
		<li><a href="login.jsp" style="padding-top: 50px">Login / Signup</a></li>
		<li><a href="index.jsp" style="padding-top: 50px">Home</a></li>
	</ul>
</div>
<div class="login-signup">
	<table>
		<tr>
			<td style="width: 48vw;" valign="top">
				<form name="login-form" action="LoginServlet" onsubmit="return validateLogin()">
					<h1 style="font-weight: normal;">Login</h1>
					<label for="username">Username</label><br>
					<input type="text" name="username" class="login-input"><br>
					<label for="password">Password</label><br>
					<input type="password" name="password" class="login-input"><br>
					<button type="submit" id="login-submit" style="background-color: #990000"><i class="fas fa-sign-in-alt"></i> 
					Sign In</button><br>
					<hr>
					<div id="customBtn"><i class="fab fa-google"></i> Sign In with Google
					</div>
				</form>
				<p style="color:red;" id="loginformerror"></p>
			</td>
			<td style="width: 48vw; padding-left: 4vw;" valign="top">
				<form name="signup" action="RegisterServlet" onsubmit="return validateRegister()">
					<h1 style="font-weight: normal;">Sign Up</h1>
					<label for="Email">Email</label><br>
					<input type="email" name="email" class=signup-input><br>
					<label for="username">Username</label><br>
					<input type="text" name="username" class="signup-input"><br>
					<label for="password">Password</label><br>
					<input type="password" name="password" class="signup-input"><br>
					<label for="confirm-password">Confirm Password</label><br>
					<input type="password" name="confirm-password" class="signup-input"><br>
					<input type="checkbox" id="terms" name="terms" value="agree">
					<label for="terms"> I have read and agree to all the terms and conditions of SalEats</label><br>
					<button type="submit" id="create-button" style="background-color: #990000">
					<i class="fas fa-user-plus"></i> Create Account</button><br>
				</form>
				<p style="color:red;" id="signupformerror"></p>
			</td>
		</tr>
	</table>
	<script>startApp();</script>
</div>
<script>
function validateLogin(){
	var xhttp = new XMLHttpRequest();
	xhttp.open("GET", "LoginValidationServlet?username=" + document["login-form"].username.value + "&password=" + document["login-form"].password.value, false);
	xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	xhttp.send();
	console.log(xhttp.responseText);
	if(xhttp.responseText.trim().length > 0){
		document.getElementById("loginformerror").innerHTML = "<p>" + xhttp.responseText + "</p";
		return false;
	}
	return true;
}
function validateRegister(){
	var xhttp = new XMLHttpRequest();
	xhttp.open("GET", "validate-register?username=" + document["signup"].username.value + "&password=" + document["signup"].password.value
			+ "&confirm=" + document.signup["confirm-password"].value + "&email=" + document["signup"].email.value
			+ "&terms=" + document["signup"].terms.checked, false);
	xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
	xhttp.send();
	console.log(xhttp.responseText);
	if(xhttp.responseText.trim().length > 0){
		document.getElementById("signupformerror").innerHTML = "<p>" + xhttp.responseText + "</p";
		return false;
	}
	return true;
}
</script>
</body>
</html>