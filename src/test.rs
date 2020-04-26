/**
 * triplet_challenge is an application that extracts the top 3 triplet words of a file
 *
 * Copyright (C) 2019 Pablo Marcos Oltra
 *
 * This file is part of triplet_challenge.
 *
 * triplet_challenge is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * triplet_challenge is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with triplet_challenge.  If not, see <http://www.gnu.org/licenses/>.
 */
use super::*;

#[test]
fn test_sanitize() {
    let string = sanitize("THiS   is\n\n\na    t35t".to_string());
    assert_eq!(string, "this   is   a    t35t");
    let words: Vec<_> = string.split_ascii_whitespace().collect();
    assert_eq!(words.len(), 4);
    assert_eq!(words, vec!["this", "is", "a", "t35t"]);
}

#[test]
fn test_generate_map() {
    let content = sanitize("this is a test to see how it goes is a test to see".to_string());
    let words: Vec<_> = content.split_ascii_whitespace().collect();
    let map = generate_map(&words);
    assert_eq!(map.len(), words.len() - 1 - 2 * 2);
    for entry in &map {
        println!("{:?} : {:?}", entry.0, entry.1);
    }
    assert_eq!(map.get(&vec!["this", "is", "a"][..]).unwrap(), &1usize);
    assert_eq!(map.get(&vec!["is", "a", "test"][..]).unwrap(), &2usize);
    assert_eq!(map.get(&vec!["a", "test", "to"][..]).unwrap(), &2usize);
    assert_eq!(map.get(&vec!["test", "to", "see"][..]).unwrap(), &2usize);
    assert_eq!(map.get(&vec!["to", "see", "how"][..]).unwrap(), &1usize);
    assert_eq!(map.get(&vec!["see", "how", "it"][..]).unwrap(), &1usize);
    assert_eq!(map.get(&vec!["how", "it", "goes"][..]).unwrap(), &1usize);
    assert_eq!(map.get(&vec!["it", "goes", "is"][..]).unwrap(), &1usize);
    assert_eq!(map.get(&vec!["goes", "is", "a"][..]).unwrap(), &1usize);
}
