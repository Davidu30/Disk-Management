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
    /// record of type Student
    /// </summary>
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class Student
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        private string id;//מספר זיהוי של הסטודנט
        public string ID//get && set of id
        {
            get
            {
                return id;
            }
            set
            {
                if ((Regex.Match(value, @"^(([0-9]){9})$").Success) || value == "0")// אם המספר מורכב רק מספרות ויש בו 9 ספרות בדיוק
                    id = value;
                else throw new Exception("ERROR: the components of ID must be 9 digits only");
            }
        }
       [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        private string address;//כתובת הסטודנט
        public string Address//get && set of address
        {
            get
            {
                return address;
            }
            set
            {
                if (value == "")
                    throw new Exception("ERROR: you must enter Address");
                address = value;
            }
        }
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        private string date_Of_birth;//תאריך הלידה של הסטודנט
        public string Date_Of_Birth
        {
            get
            {
                return date_Of_birth;
            }
            set
            {
                bool chack = Regex.Match(value, @"^(\d(\d)?/\d(\d)?/\d\d(\d\d)?)$").Success;
                if (chack)//בדיקה רגולרית אם הפורמט נכון
                    date_Of_birth = value;
                else throw new Exception("ERROR: The format of the Date of Birth incorrect");
            }
        }//get && set to date_Of_birth
    }
}
