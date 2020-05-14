<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<title>Login</title>
		<title>Register</title>
		<link rel="stylesheet" type="text/css" href="login.css">
		<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
		<!-- <link rel="stylesheet" href="/finalproject/bootstrap.min.css"> -->
		<style> a:link {text-decoration: none;}</style>
		<style> 
		input[type=submit]{
		  background-color: #636deb;
		  border: none;
		  color: white;
		  text-decoration: none;
		  cursor: pointer;
		  border-radius:25px;
	}
	</style>
	</head>
	<body>
		<div class="container">
		    <div class="row">
		      <div class="col-lg-10 col-xl-9 mx-auto">
		        <div class="card card-signin flex-row my-5">
		          <div class="card-img-left d-none d-md-flex"> </div>
		          <div class="card-body">
		             <h2 class="login-heading mb-4 withfont"><strong>sign up</strong></h2>
						<form name="register-form" method="get" action="RegisterServlet">
							<div class="formfont">
								<label for="username">Username</label><br />
								<input type="text" name="username" placeholder="Username" /><br/>
								<%if(request.getAttribute("username_error")!=null){
									String error_message = (String) request.getAttribute("username_error");%>
									<p class ="errormessage" style="color:red"><%=error_message%></p>
								<%} %>
								<label for="email">Email</label><br />
								<input type="email" name="email" placeholder="Email"/><br/>
								<%if(request.getAttribute("email_error")!=null){
									String error_message = (String) request.getAttribute("email_error");%>
									<p class ="errormessage" style="color:red"><%=error_message%></p>
								<%} %>
								<label for="password">Password</label><br />
								<input type="password" name="password" placeholder="Password" /><br />
								<%if(request.getAttribute("password_empty_error")!=null){
									String error_message = (String) request.getAttribute("password_empty_error");%>
									<p class ="errormessage" style="color:red"><%=error_message%></p>
								<%} %>
								<label for="confirm-password">Confirm Password</label><br />
								<input type="password" name="confirm-password" placeholder="Confirm-Password"/><br /><br/>
								<%if(request.getAttribute("password_match_error")!=null){
									String error_message = (String) request.getAttribute("password_match_error");%>
									<p class ="errormessage" style="color:red"><%=error_message%></p>
								<%} %>
								<input type="submit" name="submit" value="submit" /><br/>
								<br/><p><a href="index.jsp">Back to Home Page</a></p>
								
							</div>
						</form>
					 </div>
       		 	</div>
      		</div>
    	</div>
   	 </div>
					
	
	
						
	</body>
</html>