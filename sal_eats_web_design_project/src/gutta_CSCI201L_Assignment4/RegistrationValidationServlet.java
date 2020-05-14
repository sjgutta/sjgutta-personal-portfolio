package gutta_CSCI201L_Assignment4;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/RegistrationValidationServlet")
public class RegistrationValidationServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		PrintWriter out = response.getWriter();
		
		String username = request.getParameter("username");
		String password = request.getParameter("password");
		String confirm = request.getParameter("confirm");
		String email = request.getParameter("email");
		String terms = request.getParameter("terms");
		System.out.println(username + password + email + confirm);
		
		boolean info_provided = true;
		if(username.equals("") || password.equals("") || confirm.equals("") || email.equals("")) {
			out.println("Must fill in all fields<br>");
			out.flush();
			info_provided = false;
		}
		if(!terms.contentEquals("true")) {
			out.println("Must agree to the terms of service<br>");
			out.flush();
		}
		if(info_provided && !Database.verifyUserNotExists(username)) {
			out.println("A user with that username already exists<br>");
			out.flush();
		}
		if(info_provided && !password.equals(confirm)) {
			out.println("Password and confirmed password must be equal<br>");
			out.flush();
		}
		
		out.close();
	}
}
