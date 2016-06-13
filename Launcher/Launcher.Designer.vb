<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class LauncherWindow
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(LauncherWindow))
        Me.DownloadButton = New System.Windows.Forms.Button()
        Me.ProgressBar = New System.Windows.Forms.ProgressBar()
        Me.nick_txt = New System.Windows.Forms.TextBox()
        Me.Login = New System.Windows.Forms.GroupBox()
        Me.Connect = New System.Windows.Forms.Button()
        Me.port_txt = New System.Windows.Forms.TextBox()
        Me.server_txt = New System.Windows.Forms.TextBox()
        Me.Close = New System.Windows.Forms.PictureBox()
        Me.About = New System.Windows.Forms.PictureBox()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Login.SuspendLayout()
        CType(Me.Close, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.About, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'DownloadButton
        '
        Me.DownloadButton.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.DownloadButton.Font = New System.Drawing.Font("Prestige Elite Std", 15.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.DownloadButton.Location = New System.Drawing.Point(13, 620)
        Me.DownloadButton.Name = "DownloadButton"
        Me.DownloadButton.Size = New System.Drawing.Size(464, 43)
        Me.DownloadButton.TabIndex = 0
        Me.DownloadButton.Text = "Install SMW"
        Me.DownloadButton.UseVisualStyleBackColor = True
        '
        'ProgressBar
        '
        Me.ProgressBar.BackColor = System.Drawing.Color.Coral
        Me.ProgressBar.Cursor = System.Windows.Forms.Cursors.AppStarting
        Me.ProgressBar.ForeColor = System.Drawing.Color.Firebrick
        Me.ProgressBar.Location = New System.Drawing.Point(-1, 669)
        Me.ProgressBar.Name = "ProgressBar"
        Me.ProgressBar.Size = New System.Drawing.Size(488, 23)
        Me.ProgressBar.TabIndex = 1
        Me.ProgressBar.Visible = False
        '
        'nick_txt
        '
        Me.nick_txt.BackColor = System.Drawing.SystemColors.Info
        Me.nick_txt.ForeColor = System.Drawing.SystemColors.InactiveCaptionText
        Me.nick_txt.Location = New System.Drawing.Point(6, 29)
        Me.nick_txt.Name = "nick_txt"
        Me.nick_txt.Size = New System.Drawing.Size(348, 33)
        Me.nick_txt.TabIndex = 2
        Me.nick_txt.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'Login
        '
        Me.Login.BackColor = System.Drawing.Color.NavajoWhite
        Me.Login.Controls.Add(Me.Connect)
        Me.Login.Controls.Add(Me.port_txt)
        Me.Login.Controls.Add(Me.server_txt)
        Me.Login.Controls.Add(Me.nick_txt)
        Me.Login.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.Login.Font = New System.Drawing.Font("Prestige Elite Std", 15.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Login.Location = New System.Drawing.Point(117, 259)
        Me.Login.Name = "Login"
        Me.Login.RightToLeft = System.Windows.Forms.RightToLeft.Yes
        Me.Login.Size = New System.Drawing.Size(360, 137)
        Me.Login.TabIndex = 3
        Me.Login.TabStop = False
        Me.Login.Text = "Game Info"
        '
        'Connect
        '
        Me.Connect.FlatStyle = System.Windows.Forms.FlatStyle.System
        Me.Connect.Location = New System.Drawing.Point(220, 103)
        Me.Connect.Name = "Connect"
        Me.Connect.Size = New System.Drawing.Size(134, 28)
        Me.Connect.TabIndex = 3
        Me.Connect.Text = "Connect"
        Me.Connect.UseVisualStyleBackColor = True
        '
        'port_txt
        '
        Me.port_txt.BackColor = System.Drawing.SystemColors.Info
        Me.port_txt.ForeColor = System.Drawing.SystemColors.InactiveCaptionText
        Me.port_txt.Location = New System.Drawing.Point(274, 65)
        Me.port_txt.Name = "port_txt"
        Me.port_txt.Size = New System.Drawing.Size(80, 33)
        Me.port_txt.TabIndex = 2
        Me.port_txt.Text = "4242"
        Me.port_txt.TextAlign = System.Windows.Forms.HorizontalAlignment.Right
        '
        'server_txt
        '
        Me.server_txt.BackColor = System.Drawing.SystemColors.Info
        Me.server_txt.ForeColor = System.Drawing.SystemColors.InactiveCaptionText
        Me.server_txt.Location = New System.Drawing.Point(6, 65)
        Me.server_txt.Name = "server_txt"
        Me.server_txt.Size = New System.Drawing.Size(271, 33)
        Me.server_txt.TabIndex = 2
        '
        'Close
        '
        Me.Close.BackColor = System.Drawing.Color.FromArgb(CType(CType(192, Byte), Integer), CType(CType(192, Byte), Integer), CType(CType(0, Byte), Integer))
        Me.Close.Image = CType(resources.GetObject("Close.Image"), System.Drawing.Image)
        Me.Close.Location = New System.Drawing.Point(451, 2)
        Me.Close.Name = "Close"
        Me.Close.Size = New System.Drawing.Size(36, 33)
        Me.Close.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
        Me.Close.TabIndex = 4
        Me.Close.TabStop = False
        '
        'About
        '
        Me.About.BackColor = System.Drawing.Color.Khaki
        Me.About.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None
        Me.About.Image = CType(resources.GetObject("About.Image"), System.Drawing.Image)
        Me.About.Location = New System.Drawing.Point(408, 2)
        Me.About.Name = "About"
        Me.About.Size = New System.Drawing.Size(37, 33)
        Me.About.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom
        Me.About.TabIndex = 5
        Me.About.TabStop = False
        '
        'Timer1
        '
        '
        'LauncherWindow
        '
        Me.AccessibleName = "MainWindow"
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.BackgroundImage = CType(resources.GetObject("$this.BackgroundImage"), System.Drawing.Image)
        Me.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom
        Me.ClientSize = New System.Drawing.Size(489, 692)
        Me.ControlBox = False
        Me.Controls.Add(Me.About)
        Me.Controls.Add(Me.Close)
        Me.Controls.Add(Me.Login)
        Me.Controls.Add(Me.ProgressBar)
        Me.Controls.Add(Me.DownloadButton)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "LauncherWindow"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Form1"
        Me.Login.ResumeLayout(False)
        Me.Login.PerformLayout()
        CType(Me.Close, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.About, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents DownloadButton As Button
    Friend WithEvents ProgressBar As ProgressBar
    Friend WithEvents nick_txt As TextBox
    Friend WithEvents Login As GroupBox
    Friend WithEvents Connect As Button
    Friend WithEvents port_txt As TextBox
    Friend WithEvents server_txt As TextBox
    Friend WithEvents Close As PictureBox
    Friend WithEvents About As PictureBox
    Friend WithEvents Timer1 As Timer
End Class
