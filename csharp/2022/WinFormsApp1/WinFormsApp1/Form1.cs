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
            _cancellation?.Cancel();
            _cancellation = new();
            _task = Task.Factory.StartNew(IncrementCount, _cancellation.Token);
        }

        private void IncrementCount()
        {
            label1.Invoke(IncrementCountAtomic);
        }

        private void IncrementCountAtomic()
        {
            label1.Text = ++_count + "";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            _cancellation.Cancel();
        }
    }
}