package gutta_CSCI201L_Assignment4;

import java.io.IOException;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/DetailServlet")
public class DetailServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		String yelp_id = request.getParameter("yelp_id");
		int user_id = 0;
		try{
			user_id = (int) request.getSession().getAttribute("user_id");
		} catch (NullPointerException e) {
			System.out.println("No user logged in");
		}
		System.out.println("User ID is " + Integer.toString(user_id));
		request.setAttribute("favorite", false);
		if(user_id != 0) {
			boolean is_favorite = Database.already_favorite(user_id, yelp_id);
			if(is_favorite) {
				request.setAttribute("favorite", true);
			}
		}
		Restaurant restaurant = Yelp.search_yelp_by_id(yelp_id);
		request.setAttribute("restaurant", restaurant);
		String next = "/detail.jsp";
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request, response);
	}
}