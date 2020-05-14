package final_project;

import java.io.BufferedReader;
import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/SaveScheduleServlet")
public class SaveScheduleServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		
		String next = "/dashboard.jsp";
		System.out.println("saving schedule");
		
		String username = (String) request.getSession().getAttribute("username");
		String json_schedule = request.getParameter("jsonSchedule");
		System.out.println(json_schedule);
		int user_id = Database.getUserID(username);
		Database.insert_schedule(user_id, json_schedule);
		
		System.out.println("schedule saved");
		
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request, response);
	}
}