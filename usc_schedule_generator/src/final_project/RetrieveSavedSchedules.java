package final_project;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class RetrieveSavedSchedules
 */
@WebServlet("/RetrieveSavedSchedules")
public class RetrieveSavedSchedules extends HttpServlet {
	private static final long serialVersionUID = 1L;

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		
		String user =(String) request.getSession().getAttribute("username");
		
		int userID = Database.getUserID(user);
		//is userID 0 a bad userID?
		System.out.println(user + userID);
		PrintWriter out = response.getWriter();
		
		List<Schedule> list =  Database.get_user_schedules(userID);
		
		if(list.size() == 0) {
			out.println("There are no saved schedules.");
		}else {
			/*
			<div style="border-top: 1px dashed grey; border-bottom: 1px dashed grey;">
				<h1><%=course_name %></h1>
				<p>Taught by <%=professor%> in <%= classroom %><br>
				Days: <%=days %><br>
				Start: <%=start %><br>
				End: <%=end %><br>
				This section is of type: <%=course_type %></p>
			</div>
			 * */
			out.println("<table rules=\"all\" style=\"border:1px solid black\">");
			for(int i=0;i<list.size();++i) {
				out.println("<tr id=\""+list.get(i).schedule_id+"\" name=\""+i+"\">");
				out.println("<td><input type=\"radio\"  value=\""+list.get(i).schedule_id+"\" name=\"schedID\" id=\""+(list.get(i).schedule_id)+"\"/></td>");
				
				ArrayList<Course> c = list.get(i).courses;
				for(int j=0;j<c.size();++j) {
					out.println("<td valign=\"top\">");
//					out.println("<td>"+ "Course: "+c.get(j).prefix +c.get(j).code+" " +c.get(j).course_type+
//							"<br/>Days: " + c.get(j).days +"<br/>Time:" +c.get(j).start_time +"-"  +c.get(j).end_time
//							+ " <br/>Profesor: " + c.get(j).professor_name + "</td>");
					out.println("<div style=\"float: top;\">");
					out.println("<h1>"+ c.get(j).prefix +c.get(j).code +"</h1>");
					String professor ;
					professor = c.get(j).professor_name;
					if(professor.equals("")) {
						professor = "TBA";
					}
					out.println("<p>Taught by "+professor+" in "+ c.get(j).classroom+"</br>");
					out.println("Days: "+ c.get(j).days +"</br>");
					out.println("Start: "+ c.get(j).start_time+"</br>");
					out.println("End: "+ c.get(j).end_time	+"</br>");
					out.println("This section is of type:"+ c.get(j).course_type+"</p>");
					out.println("</div>");
					out.println("</td>");
				}
				
				
				out.println("</tr>");
			}
			out.println("</table>");
		}
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
