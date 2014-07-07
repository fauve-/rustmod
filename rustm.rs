#![no_std]
#![feature(lang_items)]

extern crate core;
use core::str::StrSlice;

extern { 
    pub fn printk(fmt: *const u8);
}

#[no_mangle]
unsafe fn print(s: &'static str) {
    printk(s.as_ptr());
}

#[no_mangle]
pub unsafe fn rust_main() {
    print("hello from rust\n");
}
