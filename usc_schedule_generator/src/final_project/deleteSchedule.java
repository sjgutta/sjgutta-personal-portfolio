package final_project;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class deleteSchedule
 */
@WebServlet("/deleteSchedule")
public class deleteSchedule extends HttpServlet {
	private static final long serialVersionUID = 1L;
   
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		int schedID = Integer.valueOf(request.getParameter("schedID"));
		//System.out.println(schedID);
		String name = (String)request.getSession().getAttribute("username");
		int userID = Database.getUserID(name);
		Database.delete_schedule(userID, schedID);
		PrintWriter out = response.getWriter();
		out.println(schedID);
		
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
