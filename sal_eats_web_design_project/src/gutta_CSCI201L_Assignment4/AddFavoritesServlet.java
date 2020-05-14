package gutta_CSCI201L_Assignment4;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/AddFavoritesServlet")
public class AddFavoritesServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		PrintWriter out = response.getWriter();
		String yelp_id = request.getParameter("yelp_id");
		int user_id = 0;
		try{
			user_id = (int) request.getSession().getAttribute("user_id");
		} catch (NullPointerException e) {
			System.out.println("No user logged in");
		}
		if(user_id != 0) {
			boolean is_favorite = Database.already_favorite(user_id, yelp_id);
			if(!is_favorite) {
				Database.newFavorite(user_id, yelp_id);
				out.println("yes");
			}else {
				Database.removeFavorite(user_id, yelp_id);
				out.println("no");
			}
		}
		out.flush();
		out.close();
	}
}
