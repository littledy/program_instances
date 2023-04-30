import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class ConnectionUtil {
    public static void main(String[] args) {
        Connection conn = null;
        try {
            // Class.forName("com.mysql.cj.jdbc.Driver");
            Class.forName("com.mysql.jdbc.Driver");
            String datasource = "jdbc:mysql://127.0.0.1:3306/mysql?useUnicode=true&characterEncoding=UTF-8&useSSL=false&serverTimezone=Asia/Shanghai&zeroDateTimeBehavior=CONVERT_TO_NULL&allowPublicKeyRetrieval=true";
            String user = "root";
            String password = "Dengyi@1995";
            conn = DriverManager.getConnection(datasource, user, password);
            if (conn != null) {
                System.out.println("数据库连接成功！");
                System.out.println(conn);
            }

            Statement stmt = conn.createStatement();
            String query_sql = "select * from db_audit";
            ResultSet res = stmt.executeQuery(query_sql);

            while (res.next()) {

            }
            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}
