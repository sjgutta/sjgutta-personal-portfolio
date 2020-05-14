<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>Login</title>
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
          <div class="card-body formfont">
             <h2 class="login-heading mb-4 withfont"><strong>sign in</strong></h2>
				<form name="login-form" method="get" action="LoginServlet">
					<label for="username" class="formfont"><strong>Username:</strong></label><br />
					<input type="text" name="username" placeholder="Username" class="formfont" /><br /><br />
					<label for="password" class="formfont">Password:</label><br />
					<input type="password" name="password" placeholder = "Password" class="formfont" /><br /><br />
					<input type="submit" name="submit" value="submit" class="formfont" /><br />
					<%if(request.getAttribute("error")!=null){
						String error_message = (String) request.getAttribute("error");%>
						<p class ="errormessage" style="color:red" ><%=error_message%></p>
					<%} %>
					<br/><p><a href="index.jsp" class="formfont">Back to Home Page</a></p>
				</form>
          </div>
        </div>
      </div>
    </div>

		
		
	<!--	<p><a href="index.jsp">Back to Home Page</a></p>
	<h1>Login</h1>
	<form name="login-form" method="get" action="LoginServlet">
		<div>
			<label for="username">Username:</label><br />
			<input type="text" name="username" /><br />
			<label for="password">Password:</label><br />
			<input type="password" name="password" /><br />
			<input type="submit" name="submit" value="submit" />
		</div>
	</form>
	</div>-->
	
	</div>
</body>
</html>