<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
	<head>
	<meta charset="UTF-8">
	<link rel="stylesheet" type="text/css" href="style.css">
	<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
	<!--  <link rel="stylesheet" href="/finalproject/bootstrap.min.css">-->
	<style>a:link {text-decoration: none;}	</style>	
	<title>Dashboard</title>
</head>
<body>
	<div class="container-fluid">
		<img src="image/welcome_screen.jpg"  class="img-fluid bgimage" alt="Responsive image" style = "width:100%">
		<%String user = (String) session.getAttribute("username"); 
		if(user == null){
			user = "Guest";
		}%>
		<% if(session.getAttribute("username")==null){ %>
			<p><a class="button centered2" href="login.jsp"><span>Login</span></a></p>
			<p><a class="button centered3" href="register.jsp"><span>Register</span></a></p>
		<%}else{ %>
			<p><a class="button centered2" href="savedSchedules.jsp"><span>My SChedules</span></a></p>
			<p><a class="button centered3" href="LogoutServlet"><span>Logout</span></a></p>
		<%} %>
		<div class ="dashtop-left" >Hello <a style="color:#636deb"><%=user%></a>!<br/> Welcome to the <span><a href="welcome.jsp" style="color: #990000">SC</a></span>hedget Dashboard!</div>
		<p><a class = "button centered1" href="schedule_input.jsp"><span> Find SChedule </span> </a></p>
	</div>
</body>
</html>