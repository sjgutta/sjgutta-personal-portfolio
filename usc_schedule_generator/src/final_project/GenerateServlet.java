package final_project;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/GenerateServlet")
public class GenerateServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		String next = "/schedule_input.jsp";
		
		boolean error_occurred = false;
		
		String first_prefix = request.getParameter("first_prefix");
		String first_code = request.getParameter("first_code");
		
		if(!(first_prefix == "" && first_code == "")) {
			if(Database.get_course(first_prefix, first_code).size() == 0) {
				request.setAttribute("first_error", "The first course you entered does not exist");
				error_occurred = true;
			}
		}
		
		String second_prefix = request.getParameter("second_prefix");
		String second_code = request.getParameter("second_code");
		
		if(!(second_prefix == "" && second_code == "")) {
			if(Database.get_course(second_prefix, second_code).size() == 0) {
				request.setAttribute("second_error", "The second course you entered does not exist");
				error_occurred = true;
			}
		}
		
		String third_prefix = request.getParameter("third_prefix");
		String third_code = request.getParameter("third_code");
		
		if(!(third_prefix == "" && third_code == "")) {
			if(Database.get_course(third_prefix, third_code).size() == 0) {
				request.setAttribute("third_error", "The third course you entered does not exist");
				error_occurred = true;
			}
		}
		
		String fourth_prefix = request.getParameter("fourth_prefix");
		String fourth_code = request.getParameter("fourth_code");
		
		if(!(fourth_prefix == "" && fourth_code == "")) {
			if(Database.get_course(fourth_prefix, fourth_code).size() == 0) {
				request.setAttribute("fourth_error", "The fourth course you entered does not exist");
				error_occurred = true;
			}
		}
		
		if(first_prefix == "" && second_prefix == "" && third_prefix == "" && fourth_prefix == ""
				&& first_code == "" && second_code == "" && third_code == "" && fourth_code == "") {
			request.setAttribute("none_error", "You did not enter any courses");
			error_occurred = true;
		}
		
		if(!error_occurred) {
			String time_preference = request.getParameter("time");
			Schedule result = ScheduleGenerator.generateSchedule(first_prefix, first_code, second_prefix, second_code, 
					third_prefix, third_code, fourth_prefix, fourth_code, time_preference);
			request.setAttribute("result", result);
			next = "/result.jsp";
		}
		
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request, response);
	}
}
