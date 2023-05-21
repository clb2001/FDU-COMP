package cn.xh.domain;

import java.io.Serializable;
public class Music implements Serializable{
    private String music_id;// id
    private String music_name;// name
    private String music_singer;// singer
    private String music_lyricist;
    private String music_composer;
    private String record;// record
    private String record_company;// record company
    private Category category;// category
    private String filename; // album
    private String path; // path
    private String music_description;// description
    private double music_price;// price
    private int music_inventory;// inventory
    private int music_heat;// heat

    public Music() {
        super();
        // TODO Auto-generated constructor stub
    }

    public Music(String music_id, String music_name, String music_singer, String music_lyricist,String music_composer,
                 String record, String record_company, Category category, String filename, String path,
                 String music_description, double music_price, int music_inventory, int music_heat) {
        super();
        this.music_id = music_id;
        this.music_name = music_name;
        this.music_singer = music_singer;
        this.music_lyricist = music_lyricist;
        this.music_composer = music_composer;
        this.record = record;
        this.record_company = record_company;
        this.category = category;
        this.filename = filename;
        this.path = path;
        this.music_description = music_description;
        this.music_price = music_price;
        this.music_inventory = music_inventory;
        this.music_heat = music_heat;
    }

    public String getMusic_id() {
        return music_id;
    }

    public void setMusic_id(String music_id) {
        this.music_id = music_id;
    }

    public String getMusic_name() {
        return music_name;
    }

    public void setMusic_name(String music_name) {
        this.music_name = music_name;
    }

    public String getMusic_singer() {
        return music_singer;
    }

    public void setMusic_singer(String music_singer) {
        this.music_singer = music_singer;
    }

    public String getMusic_lyricist() {
        return music_lyricist;
    }

    public void setMusic_lyricist(String music_lyricist) {
        this.music_lyricist = music_lyricist;
    }

    public String getMusic_composer() {
        return music_composer;
    }

    public void setMusic_composer(String music_composer) {
        this.music_composer = music_composer;
    }

    public String getRecord() {
        return record;
    }

    public void setRecord(String record) {
        this.record = record;
    }

    public String getRecord_company() {
        return record_company;
    }

    public void setRecord_company(String record_company) {
        this.record_company = record_company;
    }

    public Category getCategory() {
        return category;
    }

    public void setCategory(Category category) {
        this.category = category;
    }

    public String getFilename() {
        return filename;
    }

    public void setFilename(String filename) {
        this.filename = filename;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String getMusic_description() {
        return music_description;
    }

    public void setMusic_description(String music_description) {
        this.music_description = music_description;
    }

    public double getMusic_price() {
        return music_price;
    }

    public void setMusic_price(double music_price) {
        this.music_price = music_price;
    }

    public int getMusic_inventory() {
        return music_inventory;
    }

    public void setMusic_inventory(int music_inventory) {
        this.music_inventory = music_inventory;
    }

    public int getMusic_heat() {
        return music_heat;
    }

    public void setMusic_heat(int music_heat) {
        this.music_heat = music_heat;
    }

    @Override
    public String toString() {
        return "Music [music_id=" + music_id + ", music_name=" + music_name + ", music_singer=" + music_singer +
                ", music_lyricist=" + music_lyricist + ", music_composer=" + music_composer + "record:" + record
                + ", record_company=" + record_company + ", category=" + category + ", filename=" + filename + ", path=" + path
                + ", music_description=" + music_description + ", music_price=" + music_price
                + ", music_inventory=" + music_inventory + ", music_heat=" + music_heat + "]";
    }
}
