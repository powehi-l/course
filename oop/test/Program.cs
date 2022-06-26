// See https://aka.ms/new-console-template for more information
//using System;
using MySql.Data.MySqlClient;
//using System.Data.SqlClient;
//using System.Data;



namespace firs
{
    class fir
    {
        public static void Main()
        {
            string str = "server=127.0.0.1;port=3306;user=root;password=admin; database=_3200102126;";
            MySqlConnection conn = new MySqlConnection(str);
            conn.Open();
            Console.WriteLine("ok");

            MySqlCommand cmd = new MySqlCommand("select * from book",conn);
            MySqlDataReader reader = cmd.ExecuteReader();
            int j = reader.FieldCount;
            for (int i = 0; i < j; i++)
            {
                Console.Write(reader.GetName(i));
                Console.Write("\t");
            }
            Console.Write("\n");
            Console.Write(reader.GetType() + "\n");

            while (reader.Read())
            {
                if (reader.HasRows)
                {
                    for (int i = 0; i < j; i++)
                    {
                        Console.Write(reader[i]);
                        Console.Write("\t");

                    }
                    Console.Write("\n");
                }
            }

            reader.Close();
            conn.Close();
            Console.WriteLine("close");
            Console.ReadLine();
        }
    }
}
