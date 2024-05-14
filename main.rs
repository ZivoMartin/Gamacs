use std::env;
use iris::begin;

/// Parameters:
///     -j $file_name.json : export the result in the file_name.json file
///     -d "SQL REQUEST" : performs the query
///     -f $file_name.sql : execute the content of the .sql file.
///     -run: Continue to run and consume all the request in the requests file
fn main() {
    let args: Vec<String> = env::args().collect();
    begin(args);
}


