using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SampleUmlForComponents;

namespace ComponentsEvents
{
    public partial class Cities : ComboBox
    {
        public Cities()
        {
            InitializeComponent();
        }

        public Cities(IContainer container)
        {
            container.Add(this);

            InitializeComponent();
            City city_;
            city_ = new City("Paris", "300");
            city_.addSport("foot");
            city_.addSport("rugby");
            Items.Add(city_);
            city_ = new City("Lyon", "100");
            city_.addSport("foot");
            city_.addSport("rugby");
            Items.Add(city_);
            city_ = new City("Toulouse", "400");
            city_.addSport("rugby");
            Items.Add(city_);
            city_ = new City("Rouen", "500");
            city_.addSport("foot");
            city_.addSport("hockey");
            city_.addSport("basket");
            city_.addSport("rugby");
            Items.Add(city_);
        }
    }
}
