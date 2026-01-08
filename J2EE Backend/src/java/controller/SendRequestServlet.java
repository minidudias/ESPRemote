package controller;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet(name = "SendRequestServlet", urlPatterns = {"/SendRequestServlet"})
public class SendRequestServlet extends HttpServlet {
    @Override
    protected synchronized void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        // Extract the status parameter from the request
        String status = request.getParameter("status");    
        System.out.println(status);
        

        try {
            // Create a URL object
            URL url = new URL("http://192.168.8.148?status=" + status);

            // Open an HTTP connection
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");

            // Get the response code
            int responseCode = connection.getResponseCode();
            
            if (responseCode == HttpURLConnection.HTTP_OK) {
                response.setContentType("application/json");
            } else {
                response.setStatus(responseCode);
                response.getWriter().write("Failed to make request. HTTP code: " + responseCode);
            }

        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().write("Error occurred: " + e.getMessage());
        }
    }
}
