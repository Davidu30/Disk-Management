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
    /// record of type Teacher
    /// </summary>
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class Teacher
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 42)]
        private string license_number;//מספר הרישיון של המרצה 
        public string License_Number//get && set to license_number
        {
            set
            {
                if ((Regex.Match(value, @"^(([0-9]){4}$)").Success) || value == "0")//לבדות שנכנס מספר בעל 4 ספרות
                {
                    license_number = value;
                }
                else throw new Exception("ERROR: the components of License Number must be 4 digits only");
            }
            get
            {
                return license_number;
            }

        }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 42)]
        private string name;//שם
        public string Name//get&&set to name
        {
            get
            {
                return name;
            }
            set
            {
                if (value == "")
                    throw new Exception("ERROR: you must enter Name");
                name = value;
            }
        }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 42)]
        private string adress;//כתובת
        public string Adress //get&&set to adress
        {
            get
            {
                return adress;
            }
            set
            {
                if (value == "")
                    throw new Exception("ERROR: you must enter Adress");
                adress = value;
            }
        }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 42)]
        private string date_of_birth;//תאריך לידה
        public string Date_Of_Birth //get && set to date_of_birth
        {
            set
            {
                bool chack = Regex.Match(value, @"^(\d(\d)?/\d(\d)?/\d\d(\d\d)?)$").Success;
                if (chack)//בדיקה רגולרית אם הפורמט נכון
                {
                    date_of_birth = value;
                }
                else throw new Exception("ERROR: The format of the Date of Birth incorrect");
            }
            get
            {
                return date_of_birth.ToString();
            }
        }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 42)]
        private string experience_years;//שנות ניסיון
        public string Experience_Years//get and set to experience_years
        {
            get
            {
                return experience_years;
            }
            set
            {
                if (Regex.Match(value, @"^(([0-9])+$)").Success)//בדיקה שהכול מספרים
                    experience_years = value;
                else throw new Exception("ERROR: the component of Experience Years must be a digits only");
            }
        }
    }
}
