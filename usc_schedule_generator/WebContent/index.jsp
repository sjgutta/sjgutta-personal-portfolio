<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
		<title>SChedget</title>
		<link rel="stylesheet" type="text/css" href="style.css">
		<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
		<!--  <link rel="stylesheet" href="/finalproject/bootstrap.min.css">-->
		<style>a:link {text-decoration: none;}	</style>	
	</head>
	<body>
		<div class="container-fluid">
			<img src="image/welcome_screen.jpg"  class="img-fluid bgimage" alt="Responsive image" style = "width:100%">
			<!--  <div class="top-left"><STRONG>SCHEDGET</STRONG><br/></div>-->
			<!-- <div class="top-left2">A Schedule Made Just For You</div>-->
			<!--<a href="index.jsp" class="button centered" role="button"><span>get started</span></a>-->
			<div class ="top-left"><strong>Welcome to <span><a href="welcome.jsp" style="color: #990000">SC</a></span>hedget!</strong></div>
			<div class = "top-left2">A Schedule Made Just For You</div>
			<p><a class = "button centered1" href="dashboard.jsp"><span> Dashboard </span> </a></p>
			
			<% if(session.getAttribute("username")==null){ %>
			<p><a class = "button centered2" href="login.jsp"><span> Login </span></a></p>
			<p><a class ="button centered3" href="register.jsp"><span> Register</span></a></p>
			<%}else{ %>
			<!--  <p><a class ="logout" href="LogoutServlet"> Logout </a></p>-->
			<p><a class ="button centered3" href="LogoutServlet"><span> Logout</span></a></p>
			<%} %>
		
		</div>
	</body> 
		
		
		
		
	</body>
</html>