<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
	<style>
	#resultpagecontainer{
		background-image: url('image/welcome_screen.jpg');
		background-repeat:no-repeat;
		background-size:cover;
		width:90%;
		margin-bottom:40px;
		margin-top:40px;
		padding:20px;
	}
	#saveschedulebutton{
		float:right;
	}
	
	
	
	</style>

<meta charset="UTF-8">
<link rel="stylesheet" type="text/css" href="style.css">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
	<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>


<title>Result</title>
<%@ page import="final_project.Schedule, final_project.Course, com.google.gson.*" %>
<script src="https://code.jquery.com/jquery-1.10.2.js"
	type="text/javascript"></script>
</head>
<body>
<%Schedule result = (Schedule) request.getAttribute("result"); 
Gson gson = new Gson();
String json_string = gson.toJson(result); %>
<script>
	function saveSchedule(){
		console.log('called');
		var json_string = JSON.stringify(<%=json_string%>);
		console.log(json_string);
		$.ajax({
			url: 'SaveScheduleServlet',
			type: 'POST',
			data: {
				jsonSchedule: json_string
			},
			success : function response(){
				window.location.href = "dashboard.jsp";
			}
		});
		console.log("function ran");
		return false;
	}
</script>
	
		
		<nav class="navbar navbar-light bg-light justify-content-between" style="background-color: white;">
  <a class="navbar-brand" href="index.jsp" style="padding-left: 4vw;"><span style="color: #990000">SC</span><span>hedget</span></a>
  <div class="navbar-center container" style="height: 100%; width: 20%;">
  <img src="image/logo.png" style="height: auto; width: 4vw; display: block; max-width: 100%; height: auto; margin: auto" class="img-fluid">
  </div>
  <form class="form-inline" style="padding-top: 1vh; padding-right: 4vw;">
	<p style="margin-right: 1vw;"><a href="dashboard.jsp">Dashboard</a></p>
	 <% if(session.getAttribute("username")==null){ %>
				
				<p style="margin-right: 1vw;"><a href="login.jsp">Login</a></p>
				
				<p style="margin-right: 1vw;"><a href="register.jsp">Register</a></p>
				
			<%}else{ %>
				
				<p style="margin-right: 1vw;"><a href="LogoutServlet">Logout</a></p>
				
			<%} %>
  </form>
</nav>
		
		
		
		
		
<%String user = (String) session.getAttribute("username"); 
if(user == null){
	user = "Guest";
}%>




<div class = "container-fluid" id = "resultpagecontainer">
<br>
<br>
<h1>Congratulations <%=user%>! This is your generated schedule!</h1>
<% if(session.getAttribute("username")!=null){
		%><form style="float: left">
		<button type="button" id = "saveschedulebutton" class = "button" onclick="saveSchedule()">Save your schedule</button></form>
	<%} %>
	
<br>
<br>
<br>
<% for(int i=0; i<result.courses.size(); i++){
		Course course = result.courses.get(i);
		String course_name = course.prefix + course.code;
		String professor = course.professor_name;
		if(professor.equals("")){
			professor="TBA";
		}
		String classroom = course.classroom;
		String days = course.days;
		String start = course.start_time.toString();
		String end = course.end_time.toString();
		String course_type = course.course_type;%>
		
		<div style="border-top: 1px dashed grey; border-bottom: 1px dashed grey;">
			<h1><%=course_name %></h1>
			<p>Taught by <%=professor%> in <%= classroom %><br>
			Days: <%=days %><br>
			Start: <%=start %><br>
			End: <%=end %><br>
			This section is of type: <%=course_type %></p>
		</div>
		
	<%}%>
	
	

</div>
</body>
</html>