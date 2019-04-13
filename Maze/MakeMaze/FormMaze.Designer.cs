namespace MakeMaze {
    partial class FormMakeMaze {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent() {
            this.labelW = new System.Windows.Forms.Label();
            this.numericUpDownW = new System.Windows.Forms.NumericUpDown();
            this.numericUpDownH = new System.Windows.Forms.NumericUpDown();
            this.labelH = new System.Windows.Forms.Label();
            this.buttonStart = new System.Windows.Forms.Button();
            this.panelMaze = new System.Windows.Forms.Panel();
            this.pictureBoxMaze = new System.Windows.Forms.PictureBox();
            this.backgroundWorkerMakeMaze = new System.ComponentModel.BackgroundWorker();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonLoad = new System.Windows.Forms.Button();
            this.openMazeDialog = new System.Windows.Forms.OpenFileDialog();
            this.saveMazeDialog = new System.Windows.Forms.SaveFileDialog();
            this.numericUpDownColor = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.saveImageDialog = new System.Windows.Forms.SaveFileDialog();
            this.buttonSaveImage = new System.Windows.Forms.Button();
            this.numericUpDownP = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownH)).BeginInit();
            this.panelMaze.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxMaze)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownColor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownP)).BeginInit();
            this.SuspendLayout();
            // 
            // labelW
            // 
            this.labelW.AutoSize = true;
            this.labelW.Location = new System.Drawing.Point(10, 8);
            this.labelW.Name = "labelW";
            this.labelW.Size = new System.Drawing.Size(17, 12);
            this.labelW.TabIndex = 0;
            this.labelW.Text = "横";
            // 
            // numericUpDownW
            // 
            this.numericUpDownW.Location = new System.Drawing.Point(33, 6);
            this.numericUpDownW.Name = "numericUpDownW";
            this.numericUpDownW.Size = new System.Drawing.Size(51, 19);
            this.numericUpDownW.TabIndex = 1;
            this.numericUpDownW.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownW.Value = new decimal(new int[] {
            80,
            0,
            0,
            0});
            // 
            // numericUpDownH
            // 
            this.numericUpDownH.Location = new System.Drawing.Point(33, 29);
            this.numericUpDownH.Name = "numericUpDownH";
            this.numericUpDownH.Size = new System.Drawing.Size(51, 19);
            this.numericUpDownH.TabIndex = 3;
            this.numericUpDownH.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownH.Value = new decimal(new int[] {
            60,
            0,
            0,
            0});
            // 
            // labelH
            // 
            this.labelH.AutoSize = true;
            this.labelH.Location = new System.Drawing.Point(10, 31);
            this.labelH.Name = "labelH";
            this.labelH.Size = new System.Drawing.Size(17, 12);
            this.labelH.TabIndex = 2;
            this.labelH.Text = "縦";
            // 
            // buttonStart
            // 
            this.buttonStart.AutoSize = true;
            this.buttonStart.Location = new System.Drawing.Point(101, 4);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(67, 22);
            this.buttonStart.TabIndex = 4;
            this.buttonStart.Text = "迷路 生成";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // panelMaze
            // 
            this.panelMaze.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panelMaze.AutoScroll = true;
            this.panelMaze.Controls.Add(this.pictureBoxMaze);
            this.panelMaze.Location = new System.Drawing.Point(10, 52);
            this.panelMaze.Name = "panelMaze";
            this.panelMaze.Size = new System.Drawing.Size(650, 415);
            this.panelMaze.TabIndex = 5;
            this.panelMaze.Scroll += new System.Windows.Forms.ScrollEventHandler(this.panelMaze_Scroll);
            // 
            // pictureBoxMaze
            // 
            this.pictureBoxMaze.Location = new System.Drawing.Point(3, 3);
            this.pictureBoxMaze.Name = "pictureBoxMaze";
            this.pictureBoxMaze.Size = new System.Drawing.Size(100, 50);
            this.pictureBoxMaze.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBoxMaze.TabIndex = 0;
            this.pictureBoxMaze.TabStop = false;
            // 
            // backgroundWorkerMakeMaze
            // 
            this.backgroundWorkerMakeMaze.WorkerSupportsCancellation = true;
            this.backgroundWorkerMakeMaze.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorkerMakeMaze_DoWork);
            this.backgroundWorkerMakeMaze.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorkerMakeMaze_RunWorkerCompleted);
            // 
            // buttonSave
            // 
            this.buttonSave.AutoSize = true;
            this.buttonSave.Enabled = false;
            this.buttonSave.Location = new System.Drawing.Point(101, 27);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(67, 22);
            this.buttonSave.TabIndex = 6;
            this.buttonSave.Text = "迷路 保存";
            this.buttonSave.UseVisualStyleBackColor = true;
            this.buttonSave.Click += new System.EventHandler(this.buttonSave_Click);
            // 
            // buttonLoad
            // 
            this.buttonLoad.AutoSize = true;
            this.buttonLoad.Location = new System.Drawing.Point(184, 4);
            this.buttonLoad.Name = "buttonLoad";
            this.buttonLoad.Size = new System.Drawing.Size(67, 22);
            this.buttonLoad.TabIndex = 7;
            this.buttonLoad.Text = "迷路 読込";
            this.buttonLoad.UseVisualStyleBackColor = true;
            this.buttonLoad.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // openMazeDialog
            // 
            this.openMazeDialog.DefaultExt = "csv";
            this.openMazeDialog.FileName = "maze";
            this.openMazeDialog.Filter = "CSV形式|*.csv";
            this.openMazeDialog.ReadOnlyChecked = true;
            // 
            // saveMazeDialog
            // 
            this.saveMazeDialog.DefaultExt = "csv";
            this.saveMazeDialog.FileName = "maze";
            this.saveMazeDialog.Filter = "CSV形式|*.csv";
            this.saveMazeDialog.RestoreDirectory = true;
            // 
            // numericUpDownColor
            // 
            this.numericUpDownColor.DecimalPlaces = 1;
            this.numericUpDownColor.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownColor.Location = new System.Drawing.Point(361, 6);
            this.numericUpDownColor.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDownColor.Name = "numericUpDownColor";
            this.numericUpDownColor.Size = new System.Drawing.Size(51, 19);
            this.numericUpDownColor.TabIndex = 8;
            this.numericUpDownColor.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownColor.Value = new decimal(new int[] {
            6,
            0,
            0,
            0});
            this.numericUpDownColor.ValueChanged += new System.EventHandler(this.numericUpDownColor_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(254, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 9;
            this.label1.Text = "色調整値";
            // 
            // saveImageDialog
            // 
            this.saveImageDialog.DefaultExt = "png";
            this.saveImageDialog.FileName = "maze";
            this.saveImageDialog.Filter = "PNG形式|*.png";
            this.saveImageDialog.RestoreDirectory = true;
            // 
            // buttonSaveImage
            // 
            this.buttonSaveImage.AutoSize = true;
            this.buttonSaveImage.Enabled = false;
            this.buttonSaveImage.Location = new System.Drawing.Point(184, 27);
            this.buttonSaveImage.Name = "buttonSaveImage";
            this.buttonSaveImage.Size = new System.Drawing.Size(67, 22);
            this.buttonSaveImage.TabIndex = 10;
            this.buttonSaveImage.Text = "画像 保存";
            this.buttonSaveImage.UseVisualStyleBackColor = true;
            this.buttonSaveImage.Click += new System.EventHandler(this.buttonSaveImage_Click);
            // 
            // numericUpDownP
            // 
            this.numericUpDownP.Location = new System.Drawing.Point(361, 29);
            this.numericUpDownP.Name = "numericUpDownP";
            this.numericUpDownP.Size = new System.Drawing.Size(51, 19);
            this.numericUpDownP.TabIndex = 11;
            this.numericUpDownP.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericUpDownP.Value = new decimal(new int[] {
            15,
            0,
            0,
            0});
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(254, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(101, 12);
            this.label2.TabIndex = 12;
            this.label2.Text = "複数経路発生確率";
            // 
            // FormMakeMaze
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(670, 477);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.numericUpDownP);
            this.Controls.Add(this.buttonSaveImage);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.numericUpDownColor);
            this.Controls.Add(this.buttonLoad);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.panelMaze);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.numericUpDownH);
            this.Controls.Add(this.labelH);
            this.Controls.Add(this.numericUpDownW);
            this.Controls.Add(this.labelW);
            this.Name = "FormMakeMaze";
            this.Text = "Make Maze";
            this.DragDrop += new System.Windows.Forms.DragEventHandler(this.FormMakeMaze_DragDrop);
            this.DragEnter += new System.Windows.Forms.DragEventHandler(this.FormMakeMaze_DragEnter);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownH)).EndInit();
            this.panelMaze.ResumeLayout(false);
            this.panelMaze.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxMaze)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownColor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownP)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelW;
        private System.Windows.Forms.NumericUpDown numericUpDownW;
        private System.Windows.Forms.NumericUpDown numericUpDownH;
        private System.Windows.Forms.Label labelH;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Panel panelMaze;
        private System.Windows.Forms.PictureBox pictureBoxMaze;
        private System.ComponentModel.BackgroundWorker backgroundWorkerMakeMaze;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonLoad;
        private System.Windows.Forms.OpenFileDialog openMazeDialog;
        private System.Windows.Forms.SaveFileDialog saveMazeDialog;
        private System.Windows.Forms.NumericUpDown numericUpDownColor;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.SaveFileDialog saveImageDialog;
        private System.Windows.Forms.Button buttonSaveImage;
        private System.Windows.Forms.NumericUpDown numericUpDownP;
        private System.Windows.Forms.Label label2;
    }
}

