package cn.xh.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ResourceBundle;

public class JDBCUtil {
	/*
	这个变量是静态的，意味着它属于该类的所有对象共享。也就是说，无论创建多少个对象，它们都共享同一个 conn 变量。
	通常在静态成员变量中保存的是全局变量，一般用于保存需要在多个方法或多个对象之间共享的状态或数据。
	在这个例子中，这个静态变量用于保存数据库连接，以便在整个程序中都可以使用同一个连接对象，避免了重复创建连接对象的开销，提高了程序的效率。
	需要注意的是，在使用静态变量时需要特别小心，因为静态变量的生命周期和程序的生命周期一样长，如果使用不当可能会导致一些潜在的问题。
	例如，在多线程环境下使用静态变量时需要考虑线程安全问题。
	 */
	static Connection conn = null;

	static {
		// 初始化porperties文件
		/*
		ResourceBundle bundle = ResourceBundle.getBundle("jdbcConfig"); 是一个用于读取 properties 文件的 Java 语句。
		在这个语句中，ResourceBundle 是 Java 标准库中的一个类，用于加载和解析 properties 文件，并提供了一组简单的方法，可以通过键来获取对应的值。
		getBundle(String baseName) 方法是 ResourceBundle 类提供的一个静态方法，用于加载指定名称的 properties 文件。
		这个方法会搜索指定名称的 properties 文件，并返回一个 ResourceBundle 对象，该对象包含了 properties 文件中所有的键值对。
		在这个例子中，语句 ResourceBundle.getBundle("jdbcConfig") 将会查找名为 "jdbcConfig.properties" 的 properties 文件，
		并返回一个 ResourceBundle 对象，可以使用这个对象获取文件中的键值对。
		 */
		ResourceBundle bundle = ResourceBundle.getBundle("jdbcConfig");
		// driverManager = com.mysql.cj.jdbc.Driver
		// url = jdbc:mysql://localhost:3306/music_player?useSSL=false&serverTimezone=UTC
		// user=root
		// password=6514305aBc
		String dirver = bundle.getString("driverManager");
		String url = bundle.getString("url");
		String user = bundle.getString("user");
		String password = bundle.getString("password");
		// 注册驱动
		try {
			/*
			在 Java 中，不同的数据库使用不同的 JDBC 驱动程序来进行连接和操作。
			因此，在使用 JDBC 连接数据库时，需要先加载数据库对应的 JDBC 驱动程序类，才能够使用该数据库提供的功能。
			在这个语句中，Class 是 Java 标准库中的一个类，用于表示一个 Java 类。
			forName(String className) 是 Class 类提供的一个静态方法，用于加载并返回指定类名的类。
			当调用 forName() 方法时，JVM 会查找并加载指定名称的类，并返回该类对应的 Class 对象。
			在使用 JDBC 连接数据库时，我们需要先加载数据库对应的 JDBC 驱动程序类。
			例如，如果要连接 MySQL 数据库，需要使用 com.mysql.jdbc.Driver 类来进行连接和操作。
			 */
			Class.forName(dirver);
		} catch (Exception e) {
			e.printStackTrace();
		}

		try {
			/*
			DriverManager.getConnection(url, user, password) 是 Java 中用于建立数据库连接的语句，
			该语句将返回一个 java.sql.Connection 对象，用于操作数据库。
			在使用 JDBC 连接数据库时，首先需要获取一个数据库连接对象，该对象用于与数据库建立连接并进行操作。
			DriverManager 类是 Java 标准库中提供的一个类，用于管理 JDBC 驱动程序，
			其中 getConnection() 方法是 DriverManager 类提供的一个静态方法，用于创建数据库连接。
			在这个语句中，url 参数是连接字符串，用于指定要连接的数据库的位置和名称等信息。
			user 参数和 password 参数分别是连接数据库所需要的用户名和密码。
			当调用 getConnection() 方法时，JVM 会使用注册到 DriverManager 中的 JDBC 驱动程序来与指定的数据库建立连接，
			并返回一个 Connection 对象，该对象用于操作数据库。
			返回的 Connection 对象保存在名为 conn 的变量中，以供后续的数据库操作使用。
			 */
			conn = DriverManager.getConnection(url, user, password);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static Connection getConnection() {
		return conn;
	}
	
	public static void release(ResultSet set, Statement stmt, Connection connection) throws SQLException {
		if (set != null) {
			set.close();
		}
		if (stmt != null) {
			stmt.close();
		}
		if (connection != null) {
			connection.close();
		}
	}
}
