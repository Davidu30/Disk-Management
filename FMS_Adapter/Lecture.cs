using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace FMS_Adapter
{
    /// <summary>
    /// record of type Lecture
    /// </summary>
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class Lecture
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 35)]
        private String lecture_code;

        public String Lecture_Code//get&&set of medicine_code
        {
            get { return lecture_code; }
            set
            {
                if (Regex.Match(value, @"^(([0-9])+)$").Success)// אם המספר מורכב רק מספרות 
                    lecture_code = value;
                else throw new Exception("ERROR: the components of Insured Id must be digits only ");
            }
        }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 35)]
        private string lecture_name;//סוג תרופה

        public string Lecture_Name
        {
            get
            {
                return lecture_name;
            }
            set
            {
                if (value == "")
                    throw new Exception("ERROR: you must enter a lecture name");
                lecture_name = value;
            }
        }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 35)]
        private String course_cost;//מאיין שמציין את עלות הקורס

        public String Course_Cost//get&&set to drug_cost
        {
            get { return course_cost; }
            set
            {
                if (Regex.Match(value, @"^(([0-9])+)$").Success)// אם המספר מורכב רק מספרות 
                    course_cost = value;
                else throw new Exception("ERROR: the components of course Cost must be digits only ");

            }
        }
    }
}
