package gutta_CSCI201L_Assignment4;

import java.io.IOException;
import java.util.ArrayList;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


@WebServlet("/YelpServlet")
public class YelpServlet extends HttpServlet{
	public static final long serialVersionUID = 1L;
	protected void service(HttpServletRequest request, HttpServletResponse response)
		throws ServletException, IOException{
		
		String next = "/results.jsp";
		
		double latitude = Double.parseDouble(request.getParameter("latitude"));
		double longitude = Double.parseDouble(request.getParameter("longitude"));
		String name = request.getParameter("restaurant_name");
		String sort_value = request.getParameter("sort");
		
		System.out.println(latitude + " " + longitude + " " + name + " " + sort_value);
		
		ArrayList<Restaurant> results = Yelp.searchYelp(latitude, longitude, name, sort_value);
		
		request.setAttribute("results", results);
		request.setAttribute("name", name);
		
		RequestDispatcher dispatch = getServletContext().getRequestDispatcher(next);
		dispatch.forward(request, response);
	}
}
