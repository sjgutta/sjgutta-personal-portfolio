package gutta_CSCI201L_Assignment4;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/LoginValidationServlet")
public class LoginValidationServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		PrintWriter out = response.getWriter();
		
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		
		boolean credentials_provided = true;
		if(username.equals("")) {
			out.println("Must enter a username<br>");
			out.flush();
			credentials_provided = false;
		}
		if(password.equals("")) {
			out.println("Must enter a password<br>");
			out.flush();
			credentials_provided = false;
		}
		if(credentials_provided) {
			if(!Database.authenticateUser(username, password)) {
				out.println("Invalid Login Credentials<br>");
				out.flush();
			}
		}
		
		out.close();
	}
}
