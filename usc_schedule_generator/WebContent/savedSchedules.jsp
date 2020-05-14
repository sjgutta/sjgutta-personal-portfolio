<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
	<meta charset="UTF-8">
	<link rel="stylesheet" type="text/css" href="style.css">
	
	<title>Saved Schedules</title>
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
	<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
	
	<script>
		function deleteSchedule(){
			var radios = document.getElementsByName('schedID');
			console.log(radios.length);
			
			for(i=0;i<radios.length;++i){
				console.log(radios[i].value);
				if(radios[i].checked){
					//console.log('one selected');
					 $.ajax({
						url: "deleteSchedule" ,
						data:{
							schedID: radios[i].value
							
						},
						success:function(result){
							result = result.trim();
							
								//remove
								//var row = document.getElementById(radios[i].value);
								$( "#"+result ).remove();
								var radiosAfter = document.getElementsByName('schedID');
								if(radiosAfter.length == 0){
									$('#savedOnes').html("There are no saved schedules.");
								}
								
								//console.log($( "input[id=" + radios[i].value+ "]" ).val);
						}
					}); 
				}
				
				/*
				var radios = document.getElementsByName( groupName );
	   			 for( i = 0; i < radios.length; i++ ) {
	        if( radios[i].checked ) {
	            return radios[i].value;
	        }
	    }
				*/
			}
		}
	</script>
</head>
<body>
<nav class="navbar navbar-light bg-light justify-content-between" style="background-color: white;">
  <a class="navbar-brand" href="index.jsp" style="padding-left: 4vw;"><span style="color: #990000">SC</span><span>hedget</span></a>
  <div class="navbar-center container" style="height: 100%; width: 20%;">
  <img src="image/logo.png" style="height: auto; width: 4vw; display: block; max-width: 100%; height: auto; margin: auto" class="img-fluid"></img>
  </div>
  <form class="form-inline" style="padding-top: 1vh; padding-right: 4vw;">
	<p style="margin-right: 1vw;"><a href="index.jsp">Home</a></p>
	<p style="margin-right: 1vw;"><a href="dashboard.jsp">Dashboard</a></p>
	<p><a href="LogoutServlet"> Logout </a></p>
  </form>
</nav>
<div style="padding-top: 5vh; padding-left: 4vw; padding-right: 4vw; padding-bottom: 5vh;">
	<div style="z-index: 100; position: relative; display: inline-block; background-color: white;" class="bgimage">
	<%
		String user = (String) session.getAttribute("username");
		if(user == null){
			user = "Guest";
		}
		if(user.equals("Guest")){
	%>
			<p> You are a guest user, please <a href="login.jsp">login</a> or <a href="register.jsp">register</a> to be able to use this feature</p>
			<p> Go to <a href="index.jsp">Home</a></p>
	<%	
		}else{
	%>		
		<div><h1>Your Schedules</h1></div>
		<div id="savedOnes"></div>
		<script>
			$.ajax({
				url : "RetrieveSavedSchedules",
				data: {
				},
				success: function(result){
					console.log(result);
					$('#savedOnes').html(result);
				}
			
			})
			
		</script>
		
		<button type="button"  style="margin-top : 50px" onclick=deleteSchedule() >Delete</button>
	<%		
			
			
		}
	%>
	</div>
</div>
</body>
</html>