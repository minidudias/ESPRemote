package controller;
import entity.Stopping;
import java.io.IOException;
import java.util.Date;
import javax.servlet.http.HttpServlet;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import model.HibernateUtil;
import org.hibernate.Session;

@WebServlet(name = "StoppingDistanceSave", urlPatterns = {"/StoppingDistanceSave"})
public class StoppingDistanceSave extends HttpServlet{     //http://localhost:8080/ArduinoTest1/StoppingDistanceSave
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException{
                
        String distance = request.getParameter("distance");
        System.out.println(distance);
        
        Session hibernate_Session = HibernateUtil.getSessionFactory().openSession();
        
        Stopping stopping = new Stopping();
        stopping.setDate_time(new Date());
        stopping.setDistance(Double.parseDouble(distance));
        
        hibernate_Session.save(stopping);
        hibernate_Session.beginTransaction().commit();
        hibernate_Session.close();
        
    }    
}
