package gutta_CSCI201L_Assignment4;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/GoogleLoginServlet")
public class GoogleLoginServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		String next = "/index.jsp";
		String username = request.getParameter("username");
		System.out.println(username);
		String email = request.getParameter("email");
		String password = "google";
		if(!Database.googleUserExists(username)) {
			String hashed_password = Database.generateHash(password);
			Database.insertUser(username, email, hashed_password);
		}
		int id = Database.getGoogleUserID(username);
		System.out.println(id);
		request.getSession().setAttribute("user_id", id);
		request.getSession().setAttribute("google", "yes");
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request, response);
	}
}