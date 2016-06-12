Imports System.Net

Public Class LauncherWindow
    Dim strPath As String = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().CodeBase).Substring(6)
    Dim exePath As String = Application.ExecutablePath()

    Private Sub DownloadButton_Click(sender As Object, e As EventArgs) Handles DownloadButton.Click
        Dim sourceString As String = New System.Net.WebClient().DownloadString("http://petikek.eu/smw.kek")
        Dim client As WebClient = New WebClient
        AddHandler client.DownloadProgressChanged, AddressOf client_ProgressChanged
        AddHandler client.DownloadFileCompleted, AddressOf client_DownloadCompleted
        client.DownloadFileAsync(New Uri(sourceString), "data.zip")
        DownloadButton.Text = "Download in Progress"
        DownloadButton.Enabled = False
        ProgressBar.Visible = True
        Login.Visible = False
    End Sub

    Private Sub client_ProgressChanged(ByVal sender As Object, ByVal e As DownloadProgressChangedEventArgs)
        Dim bytesIn As Double = Double.Parse(e.BytesReceived.ToString())
        Dim totalBytes As Double = Double.Parse(e.TotalBytesToReceive.ToString())
        Dim percentage As Double = bytesIn / totalBytes * 100

        ProgressBar.Value = Integer.Parse(Math.Truncate(percentage).ToString())
    End Sub

    Private Sub client_DownloadCompleted(ByVal sender As Object, ByVal e As System.ComponentModel.AsyncCompletedEventArgs)
        Login.Visible = False
        If My.Computer.FileSystem.DirectoryExists(strPath + "\SuckMyWheels") Then
            My.Computer.FileSystem.DeleteDirectory((strPath + "\SuckMyWheels"), FileIO.DeleteDirectoryOption.DeleteAllContents)
        End If
        DownloadButton.Text = "Extracting File..."
        DownloadButton.Enabled = False
        ProgressBar.Visible = False
        Dim sc As Object = Activator.CreateInstance(Type.GetTypeFromProgID("Shell.Application"))
        IO.Directory.CreateDirectory((strPath + "\SuckMyWheels"))
        Dim output As Object = sc.NameSpace((strPath + "\SuckMyWheels"))
        Dim input As Object = sc.NameSpace((strPath + "\data.zip"))
        output.CopyHere((input.Items), 4)
        If My.Computer.FileSystem.FileExists(strPath + "\data.zip") Then
            My.Computer.FileSystem.DeleteFile((strPath + "\data.zip"))
        End If
        Login.Visible = True
        DownloadButton.Text = "Re-install"
        DownloadButton.Enabled = True
    End Sub

    Private Sub Launcher_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Close.BackColor = Color.Transparent
        About.BackColor = Color.Transparent
        Login.BackColor = Color.Transparent
        server_txt.Text = "server ip"
        nick_txt.Text = "nickname"

        Me.Hide()
        Splash.Show()

        If My.Computer.FileSystem.DirectoryExists(strPath + "\SuckMyWheels") Then
            Login.Visible = True
            DownloadButton.Text = "Re-install"
            DownloadButton.Enabled = True
        Else
            Login.Visible = False
            DownloadButton.Text = "Install Suck My Wheels"
            DownloadButton.Enabled = True
        End If
    End Sub

#Region " Move Form "

    Public Launcher As Boolean
    Public Launcher_MousePosition As Point

    Public Sub Launcher_MouseDown(sender As Object, e As MouseEventArgs) Handles _
    MyBase.MouseDown

        If e.Button = MouseButtons.Left Then
            Launcher = True
            Me.Cursor = Cursors.NoMove2D
            Launcher_MousePosition = e.Location
        End If

    End Sub

    Public Sub Launcher_MouseMove(sender As Object, e As MouseEventArgs) Handles _
    MyBase.MouseMove

        If Launcher Then
            Me.Location = Me.Location + (e.Location - Launcher_MousePosition)
        End If

    End Sub

    Public Sub Launcher_MouseUp(sender As Object, e As MouseEventArgs) Handles _
    MyBase.MouseUp

        If e.Button = MouseButtons.Left Then
            Launcher = False
            Me.Cursor = Cursors.Default
        End If

    End Sub

#End Region

    Private Sub Close_Click(sender As Object, e As EventArgs) Handles Close.Click
        LauncherWindow.ActiveForm.Close()
    End Sub

    Private Sub About_Click(sender As Object, e As EventArgs) Handles About.Click
        AboutForm.Show()
    End Sub

    Private Sub Connect_Click(sender As Object, e As EventArgs) Handles Connect.Click
        If server_txt.Text = "" Or port_txt.Text = "" Or nick_txt.Text = "" Then
            Return
        End If
        If My.Computer.FileSystem.FileExists(strPath + "\SuckMyWheels\Client.exe") Then
            Process.Start(strPath + "\SuckMyWheels\Client.exe", server_txt.Text + " " + port_txt.Text + " '" + nick_txt.Text + "'")
        End If
    End Sub


    Private Sub nick_txt_GotFocus(sender As Object, e As EventArgs) Handles nick_txt.GotFocus
        If nick_txt.Text = "nickname" Then
            nick_txt.Text = ""
        End If
    End Sub
    Private Sub server_txt_GotFocus(sender As Object, e As EventArgs) Handles server_txt.GotFocus
        If server_txt.Text = "server ip" Then
            server_txt.Text = ""
        End If
    End Sub
    Private Sub port_txt_GotFocus(sender As Object, e As EventArgs) Handles port_txt.GotFocus
        If port_txt.Text = "port" Then
            port_txt.Text = ""
        End If
    End Sub
    Private Sub nick_txt_LostFocus(sender As Object, e As EventArgs) Handles nick_txt.LostFocus
        If nick_txt.Text = "" Then
            nick_txt.Text = "nickname"
        End If
    End Sub
    Private Sub server_txt_LostFocus(sender As Object, e As EventArgs) Handles server_txt.LostFocus
        If server_txt.Text = "" Then
            server_txt.Text = "server ip"
        End If
    End Sub
    Private Sub port_txt_LostFocus(sender As Object, e As EventArgs) Handles port_txt.LostFocus
        If port_txt.Text = "" Then
            port_txt.Text = "port"
        End If
    End Sub

    Private Sub port_txt_TextChanged(sender As Object, e As EventArgs) Handles port_txt.TextChanged

    End Sub
End Class
