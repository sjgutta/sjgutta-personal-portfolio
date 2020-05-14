package final_project;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/RegisterServlet")
public class RegisterServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		String username = request.getParameter("username");
		String email = request.getParameter("email");
		String password = request.getParameter("password");
		String confirm_password = request.getParameter("confirm-password");
		String next = "/register.jsp";
		boolean error = false;
		if(username == "" || !Database.verifyUserNotExists(username)) {
			//user already exists
			request.setAttribute("username_error", "ERROR: You did not enter a username or a user with that username already exists.");
			error = true;
		}
		if(password == "") {
			request.setAttribute("password_empty_error", "ERROR: Must enter a password.");
			error = true;
		}
		if(email == "") {
			request.setAttribute("email_error", "ERROR: You must enter an email.");
			error = true;
		}
		if(!password.contentEquals(confirm_password)) {
			request.setAttribute("password_match_error", "ERROR: Password and confirmed password must be equal.");
			error = true;
		}
		if(!error) {
			String hashed_password = Users.generateHash(password);
			Database.insertUser(username, email, hashed_password);
			next = "/login.jsp";
		}
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request, response);
	}
}
