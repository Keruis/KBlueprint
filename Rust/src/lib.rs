use std::ffi::{CStr, CString};
use std::os::raw::c_char;
use once_cell::sync::Lazy;
use tokio::runtime::Runtime;
use reqwest::Client;

static TOKIO: Lazy<Runtime> = Lazy::new(|| Runtime::new().unwrap());
static CLIENT: Lazy<Client> = Lazy::new(|| Client::new());

fn cstr_to_str<'a>(ptr: *const c_char) -> Option<&'a str> {
    if ptr.is_null() {
        return None;
    }
    unsafe { CStr::from_ptr(ptr).to_str().ok() }
}

fn str_to_cstring(s: String) -> *mut c_char {
    CString::new(s).unwrap().into_raw()
}

async fn async_http_get(url: &str) -> Option<String> {
    match CLIENT.get(url).send().await {
        Ok(resp) => resp.text().await.ok(),
        Err(_) => None,
    }
}

async fn async_http_post(url: &str, body: &str) -> Option<String> {
    match CLIENT.post(url).body(body.to_string()).send().await {
        Ok(resp) => resp.text().await.ok(),
        Err(_) => None,
    }
}

async fn async_http_put(url: &str, body: &str) -> Option<String> {
    match CLIENT.put(url).body(body.to_string()).send().await {
        Ok(resp) => resp.text().await.ok(),
        Err(_) => None,
    }
}

async fn async_http_delete(url: &str) -> Option<String> {
    match CLIENT.delete(url).send().await {
        Ok(resp) => resp.text().await.ok(),
        Err(_) => None,
    }
}

#[no_mangle]
pub extern "C" fn http_get(url: *const c_char) -> *mut c_char {
    let url = match cstr_to_str(url) {
        Some(u) => u,
        None => return std::ptr::null_mut(),
    };
    let result = TOKIO.block_on(async_http_get(url));
    result.map_or(std::ptr::null_mut(), str_to_cstring)
}

#[no_mangle]
pub extern "C" fn http_post(url: *const c_char, body: *const c_char) -> *mut c_char {
    let url = match cstr_to_str(url) {
        Some(u) => u,
        None => return std::ptr::null_mut(),
    };
    let body = match cstr_to_str(body) {
        Some(b) => b,
        None => return std::ptr::null_mut(),
    };
    let result = TOKIO.block_on(async_http_post(url, body));
    result.map_or(std::ptr::null_mut(), str_to_cstring)
}

#[no_mangle]
pub extern "C" fn http_put(url: *const c_char, body: *const c_char) -> *mut c_char {
    let url = match cstr_to_str(url) {
        Some(u) => u,
        None => return std::ptr::null_mut(),
    };
    let body = match cstr_to_str(body) {
        Some(b) => b,
        None => return std::ptr::null_mut(),
    };
    let result = TOKIO.block_on(async_http_put(url, body));
    result.map_or(std::ptr::null_mut(), str_to_cstring)
}

#[no_mangle]
pub extern "C" fn http_delete(url: *const c_char) -> *mut c_char {
    let url = match cstr_to_str(url) {
        Some(u) => u,
        None => return std::ptr::null_mut(),
    };
    let result = TOKIO.block_on(async_http_delete(url));
    result.map_or(std::ptr::null_mut(), str_to_cstring)
}

#[no_mangle]
pub extern "C" fn http_free_string(s: *mut c_char) {
    if !s.is_null() {
        unsafe { drop(CString::from_raw(s)); }
    }
}