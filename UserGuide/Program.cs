using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Hosting;

public class Server
{
    private static IHost? _host;

    [UnmanagedCallersOnly(EntryPoint = "StartServer")]
    public static void StartServer()
    {
        Console.WriteLine("[C#] StartServer() called from native code.");

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

                _host = app;

                Console.WriteLine("[C#] ASP.NET Core app is now running.");

                await app.RunAsync();

                Console.WriteLine("[C#] ASP.NET Core app exited.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[C#] Exception: {ex}");
            }
        });

        Console.WriteLine("[C#] Task.Run for ASP.NET Core app has been launched.");
    }
}