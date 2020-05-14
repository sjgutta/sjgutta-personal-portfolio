<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<link rel="stylesheet" type="text/css" href="style.css">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
<meta charset="UTF-8">
<title>Schedule Generator</title>
</head>

<%session=request.getSession(); 
String user = (String) session.getAttribute("username");
if(user == null){
user = "Guest";
}%>
<%-- <h1>Hello <%=user %>! This is the Course Input Page.</h1> --%>
<body>

	
	
	<nav class="navbar navbar-light bg-light justify-content-between" style="background-color: white;">
  <a class="navbar-brand" href="index.jsp" style="padding-left: 4vw;"><span style="color: #990000">SC</span><span>hedget</span></a>
  <div class="navbar-center container" style="height: 100%; width: 20%;">
  <img src="image/logo.png" style="height: auto; width: 4vw; display: block; max-width: 100%; height: auto; margin: auto" class="img-fluid"></img>
  </div>
  <form class="form-inline" style="padding-top: 1vh; padding-right: 4vw; z-index:100;">
	<p style="margin-right: 1vw;"><a href="dashboard.jsp">Dashboard</a></p>
	 <% if(session.getAttribute("username")==null){ %>

				<p style="margin-right: 1vw;"><a href="login.jsp">Login</a></p>

				<p style="margin-right: 1vw;"><a href="register.jsp">Register</a></p>

			<%}else{ %>

				<p style="margin-right: 1vw;"><a href="LogoutServlet">Logout</a></p>

			<%} %>
  </form>
</nav>
	    
	 
	<div style="padding-top: 5vh; padding-left: 4vw; padding-right: 4vw; padding-bottom: 5vh; width: 100%; height: 100%">
	<div style="width: 100%; height: 100%; position: relative; display: inline-block; 
	background-image: url('image/welcome_screen.jpg'); background-repeat: no-repeat; background-size: 100% 100%" class="bgimage">
	<!-- <h1>This is where users will input their schedule!</h1> -->
	<div style="float: left;">
	<div style="text-align: left;">
	<h1>Enter your class prefixes and codes</h1>
	<h3>ex. for CSCI201, the prefix is CSCI and the code is 201</h3>
	</div>
	
	<div class="inputClassForm onTop">
	<form action="generate" style="float: left;">
	    <table>
	        <tr>
	        	<td><label>First Class Prefix</label><br>
	        		<input type="text" name="first_prefix">
	        	</td>
	        	<td>
	        		<label>First Class Code</label><br>
	        		<input type="text" name="first_code"><br>
	        	</td>
	    	</tr>
	    	<tr>
	        	<td><label>Second Class Prefix</label><br>
	        		<input type="text" name="second_prefix">
	        	</td>
	        	<td>
	        		<label>Second Class Code</label><br>
	        		<input type="text" name="second_code"><br>
	        	</td>
	    	</tr>
	    	<tr>
	        	<td><label>Third Class Prefix</label><br>
	        		<input type="text" name="third_prefix">
	        	</td>
	        	<td>
	        		<label>Third Class Code</label><br>
	        		<input type="text" name="third_code"><br>
	        	</td>
	    	</tr>
	    	<tr>
	        	<td><label>Fourth Class Prefix</label><br>
	        		<input type="text" name="fourth_prefix">
	        	</td>
	        	<td>
	        		<label>Fourth Class Code</label><br>
	        		<input type="text" name="fourth_code"><br>
	        	</td>
	    	</tr>
	    </table>
	    <label class="TOD" for="time">Time of Day Preference:</label><br>
	    <select id="time" name="time">
			<option value="early">Early Classes</option>
			<option value="later">Later Classes</option>
			<option value="middle">Mid-day Classes</option>
		</select><br>
	    <button class="but"type="submit">Generate Schedule</button>
	</form>
	</div>
	</div>
	<%if(request.getAttribute("none_error")!=null){
			String error_message = (String) request.getAttribute("none_error");%>
			<p style="color:red"><%=error_message%></p>
		<%} %>
	<%if(request.getAttribute("first_error")!=null){
			String error_message = (String) request.getAttribute("first_error");%>
			<p style="color:red"><%=error_message%></p>
		<%} %>
	<%if(request.getAttribute("second_error")!=null){
			String error_message = (String) request.getAttribute("second_error");%>
			<p style="color:red"><%=error_message%></p>
		<%} %>
	<%if(request.getAttribute("third_error")!=null){
			String error_message = (String) request.getAttribute("third_error");%>
			<p style="color:red"><%=error_message%></p>
		<%} %>
	<%if(request.getAttribute("fourth_error")!=null){
			String error_message = (String) request.getAttribute("fourth_error");%>
			<p style="color:red"><%=error_message%></p>
		<%} %>
	</div>
	</div>
	
</body>
</html>