package controller;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import entity.Stopping;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import model.HibernateUtil;
import org.hibernate.Criteria;
import org.hibernate.Session;
import org.hibernate.criterion.Order;

@WebServlet(name = "LoadDistanceData", urlPatterns = {"/LoadDistanceData"})
public class LoadDistanceData extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Gson gson = new Gson();

        JsonObject responseJson = new JsonObject();
        responseJson.addProperty("success", false);
        responseJson.addProperty("message", "Unable to Process the Request");

        try {

            Session session = HibernateUtil.getSessionFactory().openSession();

            JsonArray jsonInfoArray = new JsonArray();
            
            Criteria criteria1 = session.createCriteria(Stopping.class);
            criteria1.addOrder(Order.desc("id"));
            List<Stopping> infoList = criteria1.list();

            for (Stopping infoRecord: infoList) {                

                JsonObject infoItem = new JsonObject();
                
                infoItem.addProperty("distance", infoRecord.getDistance());
                SimpleDateFormat dateFormat = new SimpleDateFormat("hh:mm:ss a, dd MMM yy");
                infoItem.addProperty("dateTime", dateFormat.format(infoRecord.getDate_time()));

                jsonInfoArray.add(infoItem);

            }

            session.beginTransaction().commit();

            responseJson.addProperty("success", true);
            responseJson.addProperty("message", "Success");
            responseJson.add("jsonInfoArray", gson.toJsonTree(jsonInfoArray));

            session.beginTransaction().commit();
            session.close();

        } catch (Exception e) {
            e.printStackTrace();
        }

        response.setContentType("application/json");
        response.getWriter().write(gson.toJson(responseJson));
    }

}
