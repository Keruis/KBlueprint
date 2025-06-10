using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Hosting;

public class Server
{
    private static IHost? _host;
    private static readonly object _lockObj = new object();

    [UnmanagedCallersOnly(EntryPoint = "StartServer")]
    public static void StartServer()
    {
        Console.WriteLine("[C#] StartServer() called from native code.");

        lock (_lockObj)
        {
            if (_host != null)
            {
                Console.WriteLine("[C#] Server is already running.");
                return;
            }
        }

        _ = Task.Run(async () =>
        {
            try
            {
                Console.WriteLine("[C#] Starting ASP.NET Core app...");

                var builder = WebApplication.CreateBuilder();

                builder.WebHost.ConfigureKestrel(options =>
                {
                    Console.WriteLine("[C#] Configuring Kestrel to listen on port 8080...");
                    options.ListenAnyIP(8080);
                });

                var app = builder.Build();

                app.MapGet("/", async context =>
                {
                    Console.WriteLine("[C#] Serving index.html...");
                    var htmlPath = Path.Combine(AppContext.BaseDirectory, "wwwroot/index.html");
                    if (File.Exists(htmlPath))
                    {
                        context.Response.ContentType = "text/html";
                        await context.Response.SendFileAsync(htmlPath);
                    }
                    else
                    {
                        context.Response.StatusCode = 404;
                        await context.Response.WriteAsync("index.html not found.");
                    }
                });

                app.MapGet("/script.js", async context =>
                {
                    Console.WriteLine("[C#] Serving script.js...");
                    var jsPath = Path.Combine(AppContext.BaseDirectory, "wwwroot/script.js");
                    if (File.Exists(jsPath))
                    {
                        context.Response.ContentType = "application/javascript";
                        await context.Response.SendFileAsync(jsPath);
                    }
                    else
                    {
                        context.Response.StatusCode = 404;
                        await context.Response.WriteAsync("script.js not found.");
                    }
                });

                lock (_lockObj) _host = app;

                Console.WriteLine("[C#] ASP.NET Core app is now running.");

                await app.RunAsync();

                lock (_lockObj) _host = null;
                Console.WriteLine("[C#] ASP.NET Core app exited.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[C#] Exception: {ex}");
            }
        });

        Console.WriteLine("[C#] Task.Run for ASP.NET Core app has been launched.");
    }

    [UnmanagedCallersOnly(EntryPoint = "ShutdownServer")]
    public static void ShutdownServer()
    {
        Console.WriteLine("[C#] ShutdownServer() called from native code.");

        IHost? hostToShutdown = null;
        lock (_lockObj)
        {
            hostToShutdown = _host;
            _host = null;
        }

        if (hostToShutdown == null)
        {
            Console.WriteLine("[C#] No running host to shutdown.");
            return;
        }

        try
        {
            Console.WriteLine("[C#] Initiating graceful shutdown...");
            var stopTask = hostToShutdown.StopAsync(CancellationToken.None);

            stopTask.Wait(TimeSpan.FromSeconds(30));

            if (stopTask.IsCompletedSuccessfully)
            {
                Console.WriteLine("[C#] Host shutdown completed successfully.");
            }
            else
            {
                Console.WriteLine("[C#] Host shutdown timed out, forcing exit.");
            }
        }
        catch (AggregateException agEx)
        {
            foreach (var ex in agEx.InnerExceptions)
            {
                Console.WriteLine($"[C#] Shutdown error: {ex.Message}");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"[C#] Shutdown error: {ex.Message}");
        }
    }
}