using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO;

namespace MakeMaze {
    public partial class FormMakeMaze : Form {
        private Bitmap imageMaze;
        private Graphics graphics;
        private int w, h;
        private int cell = 8;
        private int[,] maze;
        private int numWall;
        private Random random = new Random();
        private SolidBrush red = new SolidBrush(Color.Red);
        private SolidBrush blue = new SolidBrush(Color.Blue);

        public FormMakeMaze() {
            InitializeComponent();
        }

        private delegate void DelegateControlVoid(Control control);
        private void controlRefresh(Control control) {
            if (control.InvokeRequired) {
                control.Invoke(new DelegateControlVoid(controlRefresh), control);
            } else {
                control.Refresh();
            }
        }

        private void showMaze() {
            graphics.Clear(Color.White);
            SolidBrush brush = new SolidBrush(Color.Green);
            int x, y;
            for (x = 0; x < 2 * w + 1; x++) {
                for (y = 0; y < 2 * h + 1; y++) {
                    if (maze[x, y] < 0) {
                        graphics.FillRectangle(blue, cell * x, cell * y, cell, cell);
                    }
                    if (maze[x, y] > 0) {
                        int i = (int)(255 * maze[x, y] / (w + h) / numericUpDownColor.Value);
                        i = Math.Min(i, 255);
                        brush.Color = Color.FromArgb(i, 255 - i, 0);
                        graphics.FillRectangle(brush, cell * x, cell * y, cell, cell);
                    }
                }
            }
            controlRefresh(pictureBoxMaze);
        }

        private void numericUpDownColor_ValueChanged(object sender, EventArgs e) {
            if (maze != null) {
                showMaze();
            }
        }

        private void panelMaze_Scroll(object sender, ScrollEventArgs e) {
            switch (e.ScrollOrientation) {
                case ScrollOrientation.HorizontalScroll:
                    panelMaze.AutoScrollPosition = new Point(e.NewValue, panelMaze.VerticalScroll.Value);
                    break;
                case ScrollOrientation.VerticalScroll:
                    panelMaze.AutoScrollPosition = new Point(panelMaze.HorizontalScroll.Value, e.NewValue);
                    break;
            }
        }

        private void buttonStart_Click(object sender, EventArgs e) {
            if (backgroundWorkerMakeMaze.IsBusy) {
                backgroundWorkerMakeMaze.CancelAsync();
            } else {
                w = (int)numericUpDownW.Value;
                h = (int)numericUpDownH.Value;
                imageMaze = new Bitmap(cell * (2 * w + 1), cell * (2 * h + 1));
                pictureBoxMaze.Image = imageMaze;
                graphics = Graphics.FromImage(imageMaze);
                buttonSave.Enabled = false;
                buttonSaveImage.Enabled = false;
                buttonStart.Text = "キャンセル";
                backgroundWorkerMakeMaze.RunWorkerAsync();
            }
        }

        private void backgroundWorkerMakeMaze_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e) {
            buttonStart.Text = "迷路作成";
            if (!e.Cancelled) {
                buttonSave.Enabled = true;
                buttonSaveImage.Enabled = true;
            }
        }

        private void backgroundWorkerMakeMaze_DoWork(object sender, DoWorkEventArgs e) {
            BackgroundWorker worker = sender as BackgroundWorker;
            maze = new int[2 * w + 1, 2 * h + 1];

            int x, y;
            // 迷路のクリア
            for (x = 0; x < 2 * w + 1; x++) {
                for (y = 0; y < 2 * h + 1; y++) {
                    maze[x, y] = 0;
                }
            }
            // 外壁作成
            for (x = 0; x < 2 * w + 1; x++) {
                maze[x, 0] = -1;
                maze[x, 2 * h] = -1;
            }
            for (y = 0; y < 2 * h + 1; y++) {
                maze[0, y] = -1;
                maze[2 * w, y] = -1;
            }
            // 壁作成
            int r, i, d1, d2, count;
            r = -1;
            d1 = -1;
            count = 0;
            for (numWall = (w - 1) * (h - 1) - 1; numWall >= 0; ) {
                if (worker.CancellationPending) {
                    break;
                }
                // まだ柱のないところを選択
                if (r < 0) {
                    r = random.Next(numWall + 1);
                    x = 0;
                    y = 2;
                    for (i = 0; i <= r; ) {
                        x += 2;
                        if (x == 2 * w) {
                            x = 2;
                            y += 2;
                        }
                        if (maze[x, y] >= 0) i++;
                    }
                }
                showMaze();
                graphics.FillRectangle(red, cell * x, cell * y, cell, cell);
                controlRefresh(pictureBoxMaze);

                // 最初は外壁から伸ばす
                if (d1 == -1 && count <= (w+h)/8) {
                    if (2 == x || x == 2 * w - 2 || 2 == y || y == 2 * h - 2) {
                        count++;
                    } else {
                        d1 = 4;
                    }
                }

                // 選んだ柱から既存の壁に接続を試みる
                if (d1 < 0) {
                    r = random.Next(4);
                    d1 = 0;
                } else {
                    r = 0;
                }
                for (; d1 < 4; d1++) {
                    switch ((d1 + r) % 4) {
                        case 0:
                            if (y - 2 >= 0 && maze[x, y - 2] < 0) {
                                maze[x, y] = -1;
                                maze[x, y - 1] = -1;
                                d1 = 4;
                            }
                            break;
                        case 1:
                            if (y + 2 <= 2 * h && maze[x, y + 2] < 0) {
                                maze[x, y] = -1;
                                maze[x, y + 1] = -1;
                                d1 = 4;
                            }
                            break;
                        case 2:
                            if (x - 2 >= 0 && maze[x - 2, y] < 0) {
                                maze[x, y] = -1;
                                maze[x - 1, y] = -1;
                                d1 = 4;
                            }
                            break;
                        case 3:
                            if (x + 2 <= 2 * w && maze[x + 2, y] < 0) {
                                maze[x, y] = -1;
                                maze[x + 1, y] = -1;
                                d1 = 4;
                            }
                            break;
                    }
                }

                // 接続できなくても壁を生成
                if (numWall % 2 == 0 && count > (w + h) / 8 && numWall >= ((w - 1) * (h - 1) - 1) * (100 - (int)numericUpDownP.Value) / 100) {
                    maze[x, y] = -1;
                }

                // 接続成功
                if (maze[x, y] < 0) {
                    numWall--;
                    // 壁を延ばす方向を決定
                    r = random.Next(4);
                    for (d2 = 0; d2 < 4; d2++) {
                        switch ((d2 + r) % 4) {
                            case 0:
                                if (y - 2 >= 0 && maze[x, y - 2] >= 0) {
                                    y = y - 2;
                                    d1 = 1;
                                    d2 = 6;
                                }
                                break;
                            case 1:
                                if (y + 2 <= 2 * h && maze[x, y + 2] >= 0) {
                                    y = y + 2;
                                    d1 = 0;
                                    d2 = 6;
                                }
                                break;
                            case 2:
                                if (x - 2 >= 0 && maze[x - 2, y] >= 0) {
                                    x = x - 2;
                                    d1 = 3;
                                    d2 = 6;
                                }
                                break;
                            case 3:
                                if (x + 2 <= 2 * w && maze[x + 2, y] >= 0) {
                                    x = x + 2;
                                    d1 = 2;
                                    d2 = 6;
                                }
                                break;
                        }
                    }
                    // 伸ばす方向が見つからなかった
                    if (d2 == 4) {
                        r = -1;
                        d1 = -1;
                    }
                } else {
                    r = -1;
                    d1 = -1;
                }
            }
            showMaze();
        }

        private void buttonSave_Click(object sender, EventArgs e) {
            if (saveMazeDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
                StreamWriter s;
                try {
                    if (null != (s = new StreamWriter(saveMazeDialog.OpenFile()))) {
                        w = (maze.GetLength(0) - 1) / 2;
                        h = (maze.GetLength(1) - 1) / 2;
                        s.Write(w); // 横
                        s.Write(',');
                        s.Write(h); // 縦
                        s.Write(s.NewLine);
                        int x, y;
                        for (y = 0; y < 2 * h + 1; y++) {
                            for (x = 0; x < 2 * w + 1; x++) {
                                s.Write(maze[x, y]);
                                if (x < 2 * w) {
                                    s.Write(',');
                                } else {
                                    s.Write(s.NewLine);
                                }
                            }
                        }
                        s.Close();
                    }
                } catch (Exception) {
                    MessageBox.Show(
                        "ファイルを開くことができませんでした．\nファイルを他のソフトで開いていませんか？",
                        "ファイルオープンエラー",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void readMaze(StreamReader s) {
            string line = s.ReadLine();
            string[] str = line.Split(',');
            numericUpDownW.Value = w = Convert.ToInt32(str[0]);
            numericUpDownH.Value = h = Convert.ToInt32(str[1]);
            maze = new int[2 * w + 1, 2 * h + 1];
            int x, y;
            for (y = 0; y < 2 * h + 1; y++) {
                line = s.ReadLine();
                str = line.Split(',');
                for (x = 0; x < 2 * w + 1; x++) {
                    maze[x, y] = Convert.ToInt32(str[x]);
                }
            }
        }

        private void buttonLoad_Click(object sender, EventArgs e) {
            if (openMazeDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
                StreamReader s = null;
                try {
                    if (null != (s = new StreamReader(openMazeDialog.OpenFile()))) {
                        readMaze(s);
                        this.Text = openMazeDialog.FileName;
                    }
                    s.Close();
                } catch (Exception ex) {
                    MessageBox.Show(
                        "ファイルを読み込むことができませんでした．\n"+ex.Message,
                        "ファイルロードエラー",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                    w = 0;
                    h = 0;
                    maze = new int[2 * w + 1, 2 * h + 1];
                    if (s != null) s.Close();
                }
                imageMaze = new Bitmap(cell * (2 * w + 1), cell * (2 * h + 1));
                pictureBoxMaze.Image = imageMaze;
                graphics = Graphics.FromImage(imageMaze);
                showMaze();
                buttonSave.Enabled = true;
                buttonSaveImage.Enabled = true;
            }
        }

        private void FormMakeMaze_DragEnter(object sender, DragEventArgs e) {
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) {
                string[] file = e.Data.GetData(DataFormats.FileDrop) as string[];
                if (file.Length == 1 && file[0].EndsWith(".csv")) {
                    e.Effect = DragDropEffects.Copy;
                } else {
                    e.Effect = DragDropEffects.None;
                }
            }
        }

        private void FormMakeMaze_DragDrop(object sender, DragEventArgs e) {
            if (e.Data.GetDataPresent(DataFormats.FileDrop)) {
                string[] file = e.Data.GetData(DataFormats.FileDrop) as string[];
                if (file.Length == 1 && file[0].EndsWith(".csv")) {
                    StreamReader s = null;
                    try {
                        if (null != (s = new StreamReader(file[0]))) {
                            readMaze(s);
                            this.Text = file[0];
                        }
                        s.Close();
                    }
                    catch (Exception ex) {
                        MessageBox.Show(
                            "ファイルを読み込むことができませんでした．\n"+ex.Message,
                            "ファイルロードエラー",
                            MessageBoxButtons.OK, MessageBoxIcon.Error);
                        w = 0;
                        h = 0;
                        maze = new int[2 * w + 1, 2 * h + 1];
                        if (s != null) s.Close();
                    }
                    imageMaze = new Bitmap(cell * (2 * w + 1), cell * (2 * h + 1));
                    pictureBoxMaze.Image = imageMaze;
                    graphics = Graphics.FromImage(imageMaze);
                    showMaze();
                    buttonSave.Enabled = true;
                    buttonSaveImage.Enabled = true;
                } else {
                    e.Effect = DragDropEffects.None;
                }
            }
        }

        private void buttonSaveImage_Click(object sender, EventArgs e) {
            if (saveImageDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
                imageMaze.Save(saveImageDialog.FileName);
            }
        }
    }
}
