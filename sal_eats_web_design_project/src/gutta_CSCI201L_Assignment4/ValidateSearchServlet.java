package gutta_CSCI201L_Assignment4;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/ValidateSearchServlet")
public class ValidateSearchServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		PrintWriter out = response.getWriter();
		
		String name = request.getParameter("name");
		String longitude = request.getParameter("longitude");
		String latitude = request.getParameter("latitude");
		String sort = request.getParameter("sort");
		System.out.println(name + latitude + longitude + sort);
		
		boolean info_provided = true;
		if(name.equals("") || longitude.equals("") || latitude.equals("")) {
			out.println("Must fill in all fields<br>");
			out.flush();
		}
		if(sort.contentEquals("")) {
			out.println("Must select a way to sort<br>");
			out.flush();
		}
		
		out.close();
	}
}
