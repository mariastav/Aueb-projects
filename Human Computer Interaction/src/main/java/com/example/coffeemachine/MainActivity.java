package com.example.coffeemachine;

import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.List;

import in.goodiebag.carouselpicker.CarouselPicker;

public class MainActivity extends AppCompatActivity {

    CarouselPicker coffees;

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.machine_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        switch (item.getItemId()) {
            case R.id.item1:
                Toast.makeText(this, "Custom Coffee selected", Toast.LENGTH_SHORT).show();
                return true;
            case R.id.item2:
                Toast.makeText(this, "Favorites selected", Toast.LENGTH_SHORT).show();
                return true;
            case R.id.item3:
                Toast.makeText(this, "Settings selected", Toast.LENGTH_SHORT).show();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        coffees = (CarouselPicker) findViewById(R.id.coffees);

        //Carousel with all images
        List<CarouselPicker.PickerItem> itemsImages = new ArrayList<>();
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.espresso));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.cappuccino));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.drycappuccino));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.flatwhite));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.latte));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.doublelatte));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.doppio));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.ristretto));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.lungo));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.macchiato));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.cafecreme));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.cafenoisette));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.americano));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.mocha));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.blackeye));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.mochabreve));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.cafeconhielo));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.cafebombon));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.conpanna));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.affogato));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.breve));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.galao));
        itemsImages.add(new CarouselPicker.DrawableItem(R.drawable.cortado));

        CarouselPicker.CarouselViewAdapter imageAdapter = new CarouselPicker.CarouselViewAdapter(this, itemsImages, 0);
        coffees.setAdapter(imageAdapter);
    }
}
