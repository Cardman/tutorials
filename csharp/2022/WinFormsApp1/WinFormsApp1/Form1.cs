namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        private Task _task;
        private CancellationTokenSource _cancellation;
        private int _count;
        public Form1() => InitializeComponent();

        private void button1_Click(object sender, EventArgs e)
        {
            _task?.Wait();
            _cancellation = new();
            _task = Task.Factory.StartNew(() =>
            {
                label1.Invoke(() => {
                    label1.Text = ++_count + "";
                });
            }, _cancellation.Token);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            _cancellation.Cancel();
        }
    }
}