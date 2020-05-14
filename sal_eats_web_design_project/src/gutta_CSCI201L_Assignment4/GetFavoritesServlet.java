package gutta_CSCI201L_Assignment4;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/GetFavoritesServlet")
public class GetFavoritesServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		int user_id = (int) request.getSession().getAttribute("user_id");
		System.out.println(user_id);
		ArrayList<Integer> favorite_ids = Database.getFavoriteIds(user_id);
		ArrayList<Restaurant> favorites = Database.getFavorites(user_id);
		System.out.println("Get favorites servlet called");
		String username = Database.getUsername(user_id);
		request.setAttribute("username", username);
		request.setAttribute("favorites", favorites);
		request.setAttribute("ids", favorite_ids);
		String next = "/favorites.jsp";
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request, response);
	}
}
